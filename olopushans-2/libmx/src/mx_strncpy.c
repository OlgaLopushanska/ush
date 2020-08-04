#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int a = 0;

    for (; src[a] && a < len; a++)
        dst[a] = src[a];
    for (; a < len; a++)
        dst[a]='\0';
    return dst;
}
