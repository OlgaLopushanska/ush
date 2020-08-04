#include "ush.h"

int mx_make_command(t_data *dat) {
    int y = -1;
    char *str = mx_itoa(mx_atoi(getenv("SHLVL")) + 1);

    setenv("SHLVL", str, 1);
    str = mx_free(str);
    for (; y == -1; ) {
        dat->exi_t = 0;
        if (dat->satty)
            str = mx_readline(str, dat);
        else 
            str = mx_file_to_str_edited(0);
        if (dat->exi_t)
            break;
        str = mx_command_create(str, &y, 0, dat);
        y = !(dat->satty) ? 0 : y;
    }
    mx_free_struct(dat);
    return y;
}
