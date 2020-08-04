#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *d = (char*)dst;
    char *s = (char*)src;

    for (unsigned long a = 0; a < n; a++)
        d[a] = s[a];
    return dst;
}


