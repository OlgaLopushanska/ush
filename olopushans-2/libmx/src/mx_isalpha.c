#include "../inc/libmx.h"

bool mx_isalpha(int c) {
    bool r = false;
    
    if (64 < c && c < 91)
        r = true;
    else if (96 < c && c < 123)
        r = true;
    return r;
}

