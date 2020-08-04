#include "ush.h"

int mx_swit( int a, char **str, int num, t_data *dat) {
    int flag = 0;
    
    if (a == 0)
        flag = mx_echo( str, num, dat);
    if (a == 1)
        flag = mx_cd(str, num, dat);
    if (a == 3)
        flag = mx_pwd(str, num, dat);
    if (a == 5)
        flag = mx_unset(str, num, dat);
    if (a == 6)
        flag = mx_env(str, num, dat);
    if (a == 4)
        flag = mx_export(str, num, dat);
    if (a == 7)
        flag = mx_which(str, num, dat);
    if (a == 8)
        flag = mx_fg(str, num, dat);
    return flag;
}
