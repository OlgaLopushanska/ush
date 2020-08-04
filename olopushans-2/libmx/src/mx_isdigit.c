#include "../inc/libmx.h"

bool mx_isdigit(int c) {
    bool r = false;
    
    if (47 < c && c < 58)
        r = true;
    return r;
}
