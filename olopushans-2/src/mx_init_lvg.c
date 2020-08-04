#include "ush.h"

t_lvg *mx_init_lvg(void) {
    t_lvg *s = (t_lvg*)malloc(sizeof(t_lvg)) ;

    s->a = 0;
    s->value = NULL;
    s->znach = NULL;
    s->fdp = 0;
    s->sign = 0;
    return s;
}
