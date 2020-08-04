#include "ush.h"

static int prepare_run(char **str, int *y, int type, t_data *dat);

static int find_builtin(char **token, int b, t_data *dat);

char *mx_command_create(char *str, int *y, int type, t_data *dat) {
    char *res = NULL;
    int fd_old[2] = {0};

    fd_old[0] = dat->fd[0];
    fd_old[1] = dat->fd[1];
    if (type == 1)
        pipe(dat->fd);
    else 
        (dat->fd)[1] = 1;
    for (; str; )
        if (prepare_run(&str, y, type, dat) == 1)
            if (!str)
                break;
    if (dat->fd[1] != 1) {
        res = mx_file_to_str_edited(dat->fd[0]);
        close(dat->fd[1]);
    }
    dat->fd[0] != 0 && dat->fd[0] != 1 ? close(dat->fd[0]) : 0;
    dat->fd[0] = fd_old[0];
    dat->fd[1] = fd_old[1];
    return res;
}

static int prepare_run(char **str, int *y, int type, t_data *dat) {
    char **token = NULL;
    int flag = 0;
    int num = 0;
    int b = 0;
    int a = 0;

    token = mx_split_line(&num, str, dat);
    if (!token || (token ? token[0] == NULL : 1)) 
        return 1;
    for (b = 0; b < num && mx_get_char_index(token[b], '=') >= 0; b++);
    flag = b == num ? mx_local_value_in(token, num, dat) : flag;
    if (b != num) {
        if ((a = find_builtin(token, b, dat)) == 2) {
            *y = mx_exit(token, num, dat);
            return 1;
        }
        if (a >= MX_NUM_COM || a == 6 || type >= 1)
            dat->child = 1;
        flag = mx_create_process(a, &token[b], num - b, dat);
        token = mx_free_array(token, num);
    }
    return 0;
}

static int find_builtin(char **token, int b, t_data *dat) {
    int a = -1;

    dat->child = 0;
    if (token != NULL)
        for (a = 0; a < MX_NUM_COM; a++)
            if (mx_strcmp(token[b], (dat->names)[a]) == 0)
                break;
    return a;
}
