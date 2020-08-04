#include "ush.h"

int main(int argc, char *argv[]) {
    t_data *dat = mx_initial();
    int res = 0;

    if (argc > 0 && argv != NULL)
        res = mx_make_command(dat);
    return res;
}
