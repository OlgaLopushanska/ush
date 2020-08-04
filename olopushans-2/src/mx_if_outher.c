#include "ush.h"

static int if_escape(char *str, int *a, int end_sign, char *temp);

static int if_quote(char str, int end_sign, int *f_q);

static char *print_error(char *temp, int *f_q, int *flag);

static void change_end_sign(t_data *dat, int *end_sign, char *str, int *a);

static int logica(char str,int end_sign);

char *mx_if_outher(char *str, int *flag, int *n_end_sign, t_data *dat) {
    char *temp = mx_strnew(mx_strlen(str));
    int end_sign = '\0';
    int a[2] = {0, 0};
    int f_q[2] = {0, 0};
    int r = 0;

    change_end_sign(dat, &end_sign, str, a);
    for (; logica(str[a[0]], end_sign) && str[a[0]] != '\0'; a[0]++) {
        if ((r = if_escape(str, a, end_sign, temp)) == 0)
            r = if_quote(str[a[0]], end_sign, f_q);
        if (r == 1)
            continue;
        else if (r == 2)
            break;
        if (str[a[0]] != '\n') {
            temp[a[1]] = str[a[0]];
            a[1]++;
        }
    }
    a[0] = end_sign == ' ' ? a[0] - 1 : a[0];
    *n_end_sign = a[0];
    return (temp = print_error(temp, f_q, flag));
}

static int if_escape(char *str, int *a, int end_sign, char *temp) {
    if (str[a[0]] == '\\') {
        if (end_sign == ' ')
            return 2;
        a[0]++;
        temp[a[1]] = str[a[0]];
        a[1]++;
        return 1;
    }
    return 0;
}

static int if_quote(char str, int end_sign, int *f_q) {
    if (str == '"' && f_q[1] == 0) {
        if (end_sign == ' ')
            return 2;
        f_q[0] = f_q[0] ? 0 : 1;
        return 1;
    }
    if (str == '\'' && f_q[0] == 0) {
        if (end_sign == ' ')
            return 2;
        f_q[1] = f_q[1] ? 0 : 1;
        return 1;
    }
    return 0;
}

static char *print_error(char *temp, int *f_q, int *flag) {
    if (f_q[0] || f_q[1]) {
        temp = mx_free(temp);
        write(2, "Odd number of quotes.\n", 22);
        *flag = 127;
    }
    return temp;
}

static void change_end_sign(t_data *dat, int *end_sign, char *str, int *a) {
    dat->flag = 0;
    *end_sign = str[0] == '{' ? '}' : *end_sign;
    *end_sign = str[0] == '(' ? ')' : *end_sign;
    *end_sign = str[0] != '{' && str[0] != '(' ? ' ' : *end_sign;
    a[0] = *end_sign == ' ' ? 0 : 1;
}

static int logica(char str,int end_sign) {
    if (end_sign != ' ')
        return str != end_sign;
    else {
        if (str == ' ' || str == ';' || str == '>' || str == '<')
            return 0;
    }
    return 1;
}
