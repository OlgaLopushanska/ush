#include "ush.h"

static char ***init_local_val(int num);

static char **init_names(void);

static int *init_spec(void);

static int *init_spec2(void);

static t_data *init_dop(t_data *dat);

t_data *mx_initial(void) {
    t_data *dat = (t_data*)malloc(sizeof(t_data));

    dat->n_val = mx_init_int(4, 1);
    dat->spec = init_spec();
    dat->spec2 = init_spec2();
    dat->wr_spec = mx_init_wr_spec();
    dat->st_val_c = init_local_val(4);
    dat->names = init_names();
    dat->fd = mx_init_int( 1, 2);
    dat->child = 0;
    dat->n_reserv = 2;
    dat->reserved = (char**)malloc(sizeof(char*) * dat->n_reserv);
    dat->reserved[0] = mx_strdup("export");
    dat->reserved[1] = mx_strdup("unset");
    dat->n_h = 0;
    dat->hist = NULL;
    dat = init_dop(dat);
    tcgetattr(0, &(dat->old_term));
    return dat;
}

static char ***init_local_val(int num) {
    int a = 0;
    char ***arr = (char***)malloc(sizeof(char**) * num);

    for (; a < num; a++)
        arr[a] = (char**)malloc(sizeof(char*) * 2);
    arr[0][0] = mx_strdup("*");
    arr[0][1] = mx_strdup(" ");
    arr[1][0] = mx_strdup("@");
    arr[1][1] = mx_strdup(" ");
    arr[2][0] = mx_strdup("?");
    arr[2][1] = mx_strdup("0");
    arr[3][0] = mx_strdup("$");
    arr[3][1] = mx_itoa(getpid());
    return arr;
}

static char **init_names(void) {
    char **names = NULL;

    names = (char**)malloc(sizeof(char*) * MX_NUM_COM);
    names[0] = mx_strdup("echo");
    names[1] = mx_strdup("cd");
    names[2] = mx_strdup("exit");
    names[3] = mx_strdup("pwd");
    names[4] = mx_strdup("export");
    names[5] = mx_strdup("unset");
    names[6] = mx_strdup("env");
    names[7] = mx_strdup("which");
    names[8] = mx_strdup("fg");
    return names;
}

static int *init_spec(void) {
    int *spec = NULL;

    spec = (int*)malloc(sizeof(int) * MX_NUM_SPEC * 2);
    spec[0] = '`';
    spec[1] = '\'';
    spec[2] = '\"';
    spec[3] = '$';
    spec[4] = '(';
    spec[5] = ')';
    spec[6] = '{';
    spec[7] = '}';
    return spec;
}

static int *init_spec2(void) {
    int *spec = NULL;

    spec = (int*)malloc(sizeof(int) * MX_NUM_SPEC2 * 2);
    spec[0] = '`';
    spec[1] = '\'';
    spec[2] = '\"';
    spec[3] = '(';
    spec[4] = '{';
    spec[0 + MX_NUM_SPEC2] = '`';
    spec[1 + MX_NUM_SPEC2] = '\'';
    spec[2 + MX_NUM_SPEC2] = '\"';
    spec[3 + MX_NUM_SPEC2] = ')';
    spec[4 + MX_NUM_SPEC2] = '}';
    return spec;
}

static t_data *init_dop(t_data *dat) {
    dat->sigi = (int*)malloc(sizeof(int));
    dat->sigi[0] = 0;
    dat->signals = (char**)malloc(sizeof(char*));
    dat->signals[0] = mx_strnew(1);
    dat->fd_name_z = NULL;
    dat->fd_name_in = NULL;
    dat->delim = NULL;
    dat->path = NULL;
    dat->satty = isatty(0);
    dat->fd_1_def = dup(STDOUT_FILENO);
    mx_check_path(NULL, 1);
    return dat;  
}
