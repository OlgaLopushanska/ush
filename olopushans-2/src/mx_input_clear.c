#include "ush.h"

void mx_input_clear(t_data *dat) {
    int a = 1;
    
    for (a = dat->cur; a <= dat->e + 5; a++)
        write(1, " ", 1);
    for (a = dat->e + 10; a >= 0; a--)
        write(1, "\b \b", 3);
}
