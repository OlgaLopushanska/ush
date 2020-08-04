#include "../inc/libmx.h"

int mx_def_start(const char *str, int sz) {
    int start = 0;

    for (int a = 0; a < sz; a++) {
        if (mx_isspace(str[a]) == false) {
            start = a;
            a = sz - 1;
        }
    }
    return start;
}

