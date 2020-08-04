#include "../inc/libmx.h"

int mx_sqrt(int x) {
    int i;

    if (x == 1)
        return 1;
    if (x <= 0)
        return 0;
    for (i = 1; i <= x; i++) {
        if (i * i == x)
            break;
        if (i != 1 && i == x)
            return 0;
    }
    return i;
}

