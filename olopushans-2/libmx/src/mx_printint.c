#include "../inc/libmx.h"

static void printint_dop(int u, int y);

void mx_printint(int n) {
    int y = 1;
    int u = 0;

    if (n == -2147483648)
        write(1, "-2147483648", 11);
    else {
        if (n < 0) {
            mx_printchar('-');
            n = n * (-1);
        }
        u = n;
        for (; n / 10 > 0; y++)
            n = n / 10;
        printint_dop(u, y);
    }
}

static void printint_dop(int u, int y) {
    for (int b = y - 1; b >= 0; b--) {
        int f = 1;

        for (int a = 1; a <= b; a++)
            f = f * 10;
            mx_printchar(u / f + '0');
            u = u % f;
    }
}

