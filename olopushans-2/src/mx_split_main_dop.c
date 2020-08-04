#include "ush.h"

t_split *mx_split_main_dop(char *str, int a, t_split *s) {
    if (mx_strlen(&str[a]) != 0) {
        s->tok = (char**)realloc(s->tok, (s->n_t + 1) * sizeof(char*));
        s->tok[s->n_t] = NULL;
        s->temp = mx_strnew(mx_strlen(str));
    }
    return s;
}
