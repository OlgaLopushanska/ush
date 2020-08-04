#include "../inc/libmx.h"

void mx_swap_char(char *s1, char *s2) {
    char t = s1[0];
    char u = s2[0];

    s1[0] = u;
    s2[0] = t;
}

