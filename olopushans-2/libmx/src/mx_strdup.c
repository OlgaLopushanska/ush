#include "../inc/libmx.h"

char *mx_strdup(const char *s1) {
    int size = mx_strlen(s1);
    char *t = mx_strnew(size);

    if (t)
        mx_strcpy(t, s1);
    return t;
}

