#include "ush.h"

static char *listen_line(int *fd, t_data *dat);

static char *read_lines(t_data *dat);

static char *read_child(int *fd, t_data *dat);

static char *read_main(int *fd, int child, t_data *dat);

char *mx_readline(char *str, t_data *dat) {
    int fd[2] = {0,0};

    pipe(fd); 
    dat->flag = 0;
    dat->cur = 0;
    mx_change_term(0, dat);
    str = listen_line(fd, dat);
    mx_change_term(1, dat);
    return str;
}

static char *listen_line(int *fd, t_data *dat) {
    pid_t child = 0;
    char *str = NULL;

    if ((child = fork()) == 0) {
        str = read_child(fd, dat);
        return NULL;
    }
    else if (child > 0)
        str = read_main(fd, child, dat);
    return str;
}

static char *read_child(int *fd, t_data *dat) {
    char *str = NULL;

    signal(SIGINT, &mx_sig_exit);
    dat->n = 0;
    dat->hist = (char**)realloc(dat->hist, sizeof(char*) * ((dat->n_h) + 1));
    dat->hist[dat->n_h] = mx_strnew(1);
    (dat->n_h)++;
    dat->n_h_t = (dat->n_h) - 1;
    dat->fd[1] = fd[1];
    str = read_lines(dat);
    if (str) {
        if (str[mx_strlen(str) - 1] == '\n')
            str[mx_strlen(str) - 1] = '\0';
        write(fd[1], str, mx_strlen(str));
    }
    close(fd[0]);
    close(fd[1]);
    dat->exi_t = 1;
    return str;
}

static char *read_main(int *fd, int child, t_data *dat) {
    char *str = NULL;
    int flag = 0; 

    mx_signals(0);
    waitpid(child, &flag, 0x00000002);
    mx_signals(1);
    str = mx_file_to_str_edited(fd[0]);
    if (str) {
        dat->hist = (char**)realloc(dat->hist, sizeof(char*)
            * ((dat->n_h) + 1));
        (dat->hist)[dat->n_h] = mx_strdup(str);
        (dat->n_h)++;
    }
    close(fd[0]);
    close(fd[1]);
    return str;
}

static char *read_lines(t_data *dat) {
    int buf = 0;
    int b = 0;
    int out = 1;
    char *res = NULL;
    int ch = 0;

    if (!(dat->delim))
        dat->delim = (int*) malloc(sizeof(int) * MX_NUM_SPEC2);
    dat->c_b = 0;
    for (b = 0; b < (int)MX_NUM_SPEC2; dat->delim[b] = 0, b++);
    for (; out == 1; ch = 0) {
        mx_read_pr_home(dat);
        if (mx_read_get_line(dat) == 1)
            continue;
        if ((buf =mx_read_check_quotes(&res, &out, dat)) == 0)
            break;
    }
    return res;
}
