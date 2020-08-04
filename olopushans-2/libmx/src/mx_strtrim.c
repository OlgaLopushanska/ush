#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    char *u = NULL;

    if (!str)
        u = NULL;
    else {
        int sz = mx_strlen(str);
        int start = mx_def_start(str, sz);
        int end = mx_def_end(str, sz);
        
        u = mx_strnew(end - start + 1);
        for (int a = 0; a <= end - start; a++)
            u[a] = str[a + start];
    }
    return u;
}

