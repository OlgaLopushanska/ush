#include "ush.h"

int mx_atoi(char *str) {
    int n = 0;
    long t = 0;
    char *rst = NULL;

    if (!str)
        return 0;
    n = mx_strlen(str);
    if (str[0] != '-')
        rst = str;
    else {
        rst = str + 1;
        n--;
    }
    for (int a = 0; a < n; a++) {
        t = t + (rst[a] - '0') * mx_pow(10.0, (n - 1 - a));
        if (t > 2147483647)
            t = 0;
    }
    return str[0] != '-' ? t : -t;
}
