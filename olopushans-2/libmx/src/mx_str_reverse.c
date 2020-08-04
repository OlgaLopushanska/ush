#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int y = 0;
 
    if(!s)
        return;
    y = mx_strlen(s) - 1;
    for (int a = 0; a <= y; a++, y--)
            mx_swap_char(&s[a], &s[y]);
}

