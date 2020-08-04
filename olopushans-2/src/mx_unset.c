#include "ush.h"

static int unset_dop(char *str, int res);

int mx_unset(char **str, int num, t_data *dat) {
    int flag = 0;
    int res = 0;
    int a = 1;
    int b = 0;

    if (num == 1) {
        write(2, "unset: not enough arguments\n", 28);
        return 1;
    }
    for (a = 1; a < num; a++) {
        if (mx_isdigit(str[a][0])) {
            flag = unset_dop(str[a], res);
            if (flag == -1)
                continue;
            if (flag == -2)
                break;
        }
        flag = unsetenv(str[a]);
        for (b = 0; b < dat->n_val[0]; b++)
            if (strcmp(str[a], dat->st_val_c[b][0]) == 0)
                dat->st_val_c[b][0][0] = '\0';
    }
    return flag;
}

static int unset_dop(char *str, int res) {
    int b = 0;

    for (b = 1; str[b] != '\0'; b++)
        if (mx_isalpha(str[b]))
            return -2;
    if (str[b] != '\0' && res == 0) {
        res = 1;
        write(2, "unset: ", 7);
        write(2, str, mx_strlen(str));
        write(2, ": invalid parameter name\n", 25);
    }
    if (str[b] != '\0')
        return -1;
    return 0;
}
