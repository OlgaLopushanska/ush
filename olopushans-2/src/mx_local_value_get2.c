#include "ush.h"

char *mx_local_value_get2(char *str, int *flag, t_data *dat) {
    char *res = NULL;
    int b = 0;
    char *temp = NULL;

    *flag = 0;
    temp = getenv(str);
    if (temp) {
        res = mx_strdup(temp);
        return res;
    }
    for (b = 0; b < dat->n_val[0]; b++) {
        if (strcmp(str, (dat->st_val_c)[b][0]) == 0) {
            res = mx_strdup((dat->st_val_c)[b][1]);
            return res;
        }
    }
    *flag = 1;
    res = mx_strnew(1);
    return res;
}
