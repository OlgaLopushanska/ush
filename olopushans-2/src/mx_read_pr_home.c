#include "ush.h"

static void print_quote(t_data *dat);

void mx_read_pr_home(t_data *dat) {
    int a = 0;
    int b = 0;

    dat->b = 0;
    dat->e = 0;
    if (!(dat->path)) {
        dat->b = (dat->b) + write(1, "\ru$h ", 5);
        mx_print_folder(dat);
        dat->b = (dat->b) + write(1, " > ", 3); 
    }
    else
        print_quote(dat);
    a = dat->n_h_t;
    b = dat->c_b;
    dat->e = (dat->e) +
        write(1, &(dat->hist)[a][b], mx_strlen(&(dat->hist)[a][b]));
    if (mx_strlen((dat->hist)[dat->n_h_t]) > 0)
        for (a = dat->e; a > dat->cur; a--)
            write(1, "\b", 1);
}

static void print_quote(t_data *dat) {
    int a = 0;
    int b = 0;
    int k = 0;

    write(1, "\r", 1);
    for (b = 0; b < dat->n; b++) {
        k = dat->path[b];
        k = write(1, (dat->wr_spec)[k], mx_strlen((dat->wr_spec)[k]));
        dat->b = (dat->b) + k;
        a = b == (dat->n) - 1 ? write(1, "> ", 2) : write(1, " ", 1);
        dat->b = (dat->b) + a;
        dat->c_b = mx_strlen((dat->hist)[dat->n_h_t]);
        dat->cur = 0;
    }
}
