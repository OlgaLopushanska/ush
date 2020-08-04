#include "../inc/libmx.h"

bool mx_isspace(char c) {
    bool b = false;
    char s[6] = {' ', '\t', '\v', '\n', '\f', '\r'};
    int priznak = 0;

    for (int a = 0; a < 6; a++) {
        if (c == s[a])
            priznak++;
        if(priznak > 0)
            b = true;
    }
    return b;
}

