#include "../inc/libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int a = 0;

    for (a = 0; src[a] != '\0'; a++)
        dst[a] = src[a];
    dst[a] = '\0';
    return dst;
}

