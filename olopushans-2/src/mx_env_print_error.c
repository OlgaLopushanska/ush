#include "ush.h"

void mx_env_print_error(char **in) {
    write(2, "env: ", 5);
    write(2, in[0], mx_strlen(in[0]));
    write(2, ": No such file or directory\n", 28);
}
