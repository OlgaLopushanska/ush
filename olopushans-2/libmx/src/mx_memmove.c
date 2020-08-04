#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *res = mx_strnew(len);
    char *d = (char*)dst;
    char *s = (char*)src;

    for (unsigned long a = 0; a < len; a++)
        res[a] = s[a];
    for (unsigned long a = 0; a < len; a++)
        d[a] = res[a];
    free(res);
    return d;
}


