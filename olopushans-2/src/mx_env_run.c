#include "ush.h"

void mx_env_run(char **str, int num, int a, char *path) {
    int flag = 0;
    int b = 0;
    char **in = NULL;

    for (b = 0; a < num; a++, b++) {
        in = (char**)realloc(in, sizeof(char*) * (b + 1));
        in[b] = str[a];
    }
    in = (char**)realloc(in, sizeof(char*) * (b + 1));
    in[b] = NULL;
    if (in[0])
        flag = path ? execv(path, in) : execvp(in[0], in);
    else
        return;
    mx_env_print_error(in);
    in = mx_free(in);
}
