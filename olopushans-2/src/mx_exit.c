#include "ush.h"

int mx_exit(char **str, int num, t_data *dat) {
    int a = 0;
    char *s = NULL;
    int res = 0;
    int flag = 1;

    dat->flag = 0;
    if (num > 2) {
        write(2, "exit: too many arguments\n", 25);
        return 1;
    }
    if (str[1]) {
        for (; str[a] != '\0'; a++)
            flag = mx_isdigit(str[1][a]) ? flag : 0;
        if (flag)
            res = mx_atoi(str[1]);
    }
    s = mx_itoa(mx_atoi(getenv("SHLVL")) - 1);
    setenv("SHLVL", s, 1);
    s = mx_free(s);
    str = mx_free_array(str, num);
    return res;
}
