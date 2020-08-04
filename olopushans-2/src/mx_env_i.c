#include "ush.h"

static char **env_i_input(char **str, int num, int *a, t_data *dat);

static int env_i_input_dop(char **str, int *a, char ***in, int *priz);

int mx_env_i(char **str, int a, int num, t_data *dat) {
    int flag = 0;
    char **in = NULL;
    char *path = NULL;
    
    flag = mx_clearenv();
    in = env_i_input(str, num, &a, dat);
    if (in[0])
        flag = execvp(in[0], in);
    else
        return 1;
    mx_env_print_error(in);
    in = mx_free(in);
    mx_env_run(str, num, a, path);
    return 1;
}

static char **env_i_input(char **str, int num, int *a, t_data *dat) {
    char **in = NULL;
    int b = 0;
    int flag = 0;
    int priz = 0;

    in = (char**)realloc(in, sizeof(char*) * 1);
    in[0] = NULL;
    b = env_i_input_dop(str, a, &in, &priz);
    if (priz) {
        in[0] = mx_strdup("export");
        flag = mx_export(in, b, dat);
    }
    in = mx_free_array(in, b);
    for (b = 0; *a < num; (*a)++, b++) {
        in = (char**)realloc(in, sizeof(char*) * (b + 1));
        in[b] = str[*a];
    }
    in = (char**)realloc(in, sizeof(char*) * (b + 1));
    in[b] = NULL;
    return in;
}

static int env_i_input_dop(char **str, int *a, char ***in, int *priz) {
    int b = 0;

    for (b = 1; mx_get_char_index(str[*a], '=') >= 0; (*a)++, b++) {
        *in = (char**)realloc(*in, sizeof(char*) * (b + 1));
        (*in)[b] = str[*a];
        *priz = 1;
    }
    return b;
}
