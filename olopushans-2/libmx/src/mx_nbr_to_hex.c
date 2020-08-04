#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long n = nbr;
    char *e;
    int p = 1;
    int t = 0;

    if (n < 16)
        p = 1;
    else 
        for (; n / 16 > 0; p++)
            n = n / 16;
    e = mx_strnew(p);
    for (int a = p - 1; a >= 0; a--) {
        t = nbr % 16;
        if (t >= 0 && t <= 9)
            e[a] = t + 48;
        else if (t >= 10 && t <= 16)
            e[a] = (t + 97 - 10);
        nbr = nbr / 16;
    }
    return e;
}


