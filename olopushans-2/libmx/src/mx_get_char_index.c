#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    int y = -1;

    if (str == NULL) 
        y = -2;
    else {
        for (int a = 0; str[a] != '\0' || y != -1; a++) {
            if (str[a] == c) {
                y = a;
                break;
            }
        }
    }
    return y;
}
