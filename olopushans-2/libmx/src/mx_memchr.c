#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *p = (char*)s;
    char *d = NULL;

    for (unsigned long a = 0; a < n; a++) {
        if (p[a] == c) {
            d = &p[a];
            a = n;
        }
    }
    return d;
}


