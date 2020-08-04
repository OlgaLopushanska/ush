#include "ush.h"

static char *find_value(char *str, int *flag, t_lvg *s, t_data *dat);

static int if_lvg_error(char *str, int log, t_lvg *s);

static int lvg_d1(char *str, char **res, t_lvg *s, t_data *dat);

static void lvg_d2(int *flag, char **res, t_lvg *s) ;

char *mx_local_value_get(char *str, int *flag, t_data *dat) {
    t_lvg *s = mx_init_lvg();
    char *res = NULL;

    *flag = 0;
    res = find_value(str, flag, s, dat);
    if (str[s->a] == '\0') {
        s = mx_free(s);
        return res;
    }
    if (if_lvg_error(str, *flag == 0 && (s->fdp ? res[0] != '\0' : 1), s)) {
        s = mx_free(s);
        return res;
    }
    *flag = lvg_d1(str, &res, s, dat);
    lvg_d2(flag, &res, s);
    s = mx_free(s);
    return res;
}

static char *find_value(char *str, int *flag, t_lvg *s, t_data *dat) {
    char *res = NULL;

    s->value = mx_strnew(mx_strlen(str));
    for (s->a = 0; (mx_isdigit(str[s->a]) != 0
        || mx_isalpha(str[s->a]) != 0) && str[s->a] != 0; (s->a)++)
        s->value[s->a] = str[s->a];
    res = mx_local_value_get2(s->value, flag, dat);
    return res;
}

static int if_lvg_error(char *str, int log, t_lvg *s) {
    if (str[s->a] == ':') {
        s->fdp = 1;
        (s->a)++;
    }
    s->sign = str[s->a];
    if (s->sign != '+')
        if (log)
            return 1;
    return 0;
}

static int lvg_d1(char *str, char **res, t_lvg *s, t_data *dat) {
    int flag = 0;
    int b = 0;

    if (str[++(s->a)] == '`' || (str[s->a] == '$'))
        s->znach = mx_run_doch(&str[s->a], &flag, &b, dat);
    else {
        s->znach = mx_strnew(mx_strlen(str));
        for (b = 0; mx_isdigit(str[s->a]) != 0; b++, (s->a)++) {
            s->znach[b] = str[s->a];
        }
    }
    if (s->sign == '-' || s->sign == '=') {
        *res = mx_free(*res);
        *res = mx_strdup(s->znach);
        if (s->sign == '=') {
            mx_local_value_in2(dat, &(s->value), -1, s->znach);
        }
    }
    return flag;
}

static void lvg_d2(int *flag, char **res, t_lvg *s) {
    if (s->sign == '+') {
        if (*flag == 0 && (s->fdp ? (*res)[0] != '\0' : 1)) {
            *res = mx_free(*res);
            *res = mx_strdup(s->znach);
        }
    }
    if (s->sign == '?') {
        write(2, s->znach, mx_strlen(s->znach));
        write(2, "\n", 1);
    }
}
