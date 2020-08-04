#include "ush.h"

static char *bquotes(char *str, int *flag, int *n_end_sign, t_data *dat);

char *mx_run_doch(char *str, int *flag, int *n_end_sign, t_data *dat) {
    char *result = NULL;

    if (str[0] == '`')
        result = bquotes(str, flag, n_end_sign, dat);
    else if (str[0] == '$') {
        result = mx_if_outher(&str[1], flag, n_end_sign, dat);
        if (str[1] == '(')
            result = mx_command_create(result, flag, 1, dat);
        else if (str[1] == '{')
            result = mx_local_value_get(result, flag, dat);
        else 
            result = mx_local_value_get2(result, flag, dat);
        (*n_end_sign)++;
    }
    else if (str[0] == '(') {
        result = mx_if_outher(&str[0], flag, n_end_sign, dat);
        if (result)
            result = mx_command_create(result, flag, 2, dat);
    }
    return result;
}

static char *bquotes(char *str, int *flag, int *n_end_sign, t_data *dat) {
    int a = 0;
    int n = 0;
    char *temp = mx_strnew(mx_strlen(str));

    for (a = 1; str[a] != '\0' && str[a] != '`'; a++) {
        if (str[a] == '\0') {
            temp = mx_free(str);
            write(2, "Odd number of quotes.\n", 22);
            *flag = 127;
            return temp;
        }
        if (str[a] == '\\') {
            a = mx_if_escape(str, a, NULL);
            temp[n] = str[a];
            n++;
            continue;
        }
        temp[n] = str[a];
        n++;
    }
    *n_end_sign = a;
    if (temp)
        temp = mx_command_create(temp, flag, 1, dat);
    return temp;
}
