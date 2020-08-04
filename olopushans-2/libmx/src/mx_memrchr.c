#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *p = (char*)s;
    char *d = NULL;

    for (int a = n - 1; a >= 0; a--) {
        if (p[a] == c) {
            d = &p[a];
            a = -1;
        }
    }
    return d;
}


