#include "ush.h"

static void read1(char *red, int b, t_data *dat);

static char *read2(char *red, char *temp, int b, t_data *dat);

static int read3(char *red, char **temp, int b, t_data *dat);

int mx_read_get_line(t_data *dat) {
    int ch = 0;
    char *red = NULL;
    int buf = 0;
    int b = 0;
    char *temp = NULL;

    for (; ; ch = 0) {
        red = mx_strnew(100);
        if ((b = read(0, red, 10)) > 0) {
            if (red[0] == '\n')
                break;
            dat->e = (dat->e) + b;
            buf = buf + b;
            if ((ch = read3(red, &temp, b, dat)) == 1)
                break;
        }
        red = mx_free(red);
    }
    return ch;
}

static int read3(char *red, char **temp, int b, t_data *dat) {
    int ch = 0;

    if ((ch = mx_spec_commands(red, b, dat)) == 1)
        return ch;
    if (!dat->c_b) {
        read1(red, b, dat);
        ch = 1;
    }
    else
        *temp = read2(red, *temp, b, dat);
    return ch;
}

static void read1(char *red, int b, t_data *dat) {
    char *s1 = NULL;
    char *s2 = NULL;

    s1 = mx_strndup(dat->hist[dat->n_h_t], dat->cur);
    s2 = mx_strjoin(s1, red);
    s1 = mx_free(s1);
    s1 = mx_strjoin(s2, &(dat->hist)[dat->n_h_t][dat->cur]);
    (dat->hist)[dat->n_h_t] = mx_free((dat->hist)[dat->n_h_t]);
    (dat->hist)[dat->n_h_t] = s1;
    dat->cur = (dat->cur) + b;
}

static char *read2(char *red, char *temp, int b, t_data *dat) {
    char *s1 = NULL;
    char *s2 = NULL;

    if (temp)
        s1 = mx_strndup(temp, dat->cur);
    else
        s1 = mx_strnew(1) ;
    s2 = mx_strjoin(s1, red);
    s1 = mx_free(s1);
    s1 = mx_strjoin(s2, &temp[dat->cur]);
    temp = mx_free(temp);
    temp = s2;
    s1 = mx_strjoin((dat->hist)[dat->n_h_t], temp);
    (dat->hist)[dat->n_h_t] = mx_free((dat->hist)[dat->n_h_t]);
    (dat->hist)[dat->n_h_t] = s1;
    dat->cur = (dat->cur) + b;
    return temp;
}
