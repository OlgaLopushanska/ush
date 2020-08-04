#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    int y = 0;

    for (; *s; s++)
        y++;
    return y;
}


