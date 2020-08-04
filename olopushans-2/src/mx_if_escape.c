#include "ush.h"

int mx_if_escape(char *str, int a, t_split *s) {
    char str_old = 0;
    int k = 0;

    if (str)
        if (str[a] == '\\')
            if (mx_strlen(&str[a]) >= 2) {
                a++;
                str_old = str[a];
                str[a] = str[a] == 'n' ? '\n' : str[a];
                str[a] = str[a] == '0' ? '\0' : str[a];
                str[a] = str[a] == 'b' ? '\b' : str[a];
                str[a] = str[a] == 't' ? '\t' : str[a];
                str[a] = str[a] == 'a' ? '\a' : str[a];
                str[a] = str[a] == 'v' ? '\v' : str[a];
                str[a] = str[a] == 'f' ? '\f' : str[a];
                str[a] = str[a] == 'r' ? '\r' : str[a];
                k = s ? s->f_dq != 0 || s->f_q != 0 : 0;
                if (str_old == str[a] && str[a] != '\\' && k)
                    a--;
            }
    return a;
}
