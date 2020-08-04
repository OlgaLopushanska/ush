#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    int y = mx_strlen(hex);
    unsigned long n = 0;

    for (int a = 0; a < y; a++) {
        unsigned long x = 1;
        int r = 0;

        for (r = 0; r < (y - a); r++) {
            x = x * 16;
            if (r == 0)
                x = 1;
        }
        if (hex[a] > 48 && hex[a] <= 57)
            n = n + ((hex[a] - 48) * x);
        else if (hex[a] >= 'A' && hex[a] <= 'F')
            n = n + (hex[a] - 55) * x;
        else if (hex[a] >= 'a' && hex[a] <= 'f')
            n = n + (hex[a] - 87) * x;
    }
    return n;
}
