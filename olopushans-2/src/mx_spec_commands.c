#include "ush.h"

static void spec_commands_dop1(char *red, t_data *dat, int *flag);

static void spec_commands_dop2(char *red, t_data *dat, int *flag);

static void spec_commands_dop3(char *red, t_data *dat, int *flag, int *a);

static int if_else(char red, int flag, t_data *dat);

int mx_spec_commands(char *red, int b, t_data *dat) {
    int flag = 0;
    int a = b;

    spec_commands_dop1(red, dat, &flag);
    if (mx_get_substr_index(red, "\x1A") >= 0) {
        mx_input_clear(dat);
        flag = 1;
    }
    if (mx_get_substr_index(red, "\x7f") >= 0) {
        mx_input_clear(dat);
        dat->cur = dat->cur <= 0 ? 0 : (dat->cur) - 1;
        if (dat->cur >= 0)
            for (a = dat->cur; (dat->hist)[dat->n_h_t][a] != '\0'; a++)
                (dat->hist)[dat->n_h_t][a] = (dat->hist)[dat->n_h_t][a + 1];
        flag = 1;
    }
    spec_commands_dop2(red, dat, &flag);
    spec_commands_dop3(red, dat, &flag, &a);
    return (flag = if_else(red[0], flag, dat));
}

static void spec_commands_dop1(char *red, t_data *dat, int *flag) {
    if (mx_get_substr_index(red, "\x03") >= 0) {
        mx_change_term(1, dat);
        mx_input_clear(dat);
        mx_free_struct(dat);
        write(1, "\n", 1);
        *flag = 1;
        exit(0);
    }
    if (mx_get_substr_index(red, "\x04") >= 0) {
        mx_change_term(1, dat);
        write(dat->fd[1], "exit", 4);
        mx_free_struct(dat);
        *flag = 1;
        exit(0);
    }
}

static void spec_commands_dop2(char *red, t_data *dat, int *flag) {
    if (mx_get_substr_index(red, "\x1b[A") >= 0) {
        dat->n_h_t = dat->n_h_t <= 0 ? 0 : (dat->n_h_t) - 1;
        mx_input_clear(dat);
        dat->cur = mx_strlen(dat->hist[dat->n_h_t]);
        *flag = 1;
    }
    if (mx_get_substr_index(red, "\x1b[B") >= 0) {
        dat->n_h_t = (dat->n_h_t) + 1 >= dat->n_h ? (dat->n_h) - 1
            : (dat->n_h_t) + 1;
        mx_input_clear(dat);
        dat->cur = mx_strlen(dat->hist[dat->n_h_t]);
        *flag = 1;
    }
    if (mx_get_substr_index(red, "\x1b[D") >= 0) {
        dat->cur = (dat->cur) - 1 <= 0 ? 0 : (dat->cur) - 1;
        mx_input_clear(dat);
        *flag = 1;
    }
}

static void spec_commands_dop3(char *red, t_data *dat, int *flag, int *a) {
    if (mx_get_substr_index(red, "\x1b[C") >= 0) {
        *a = mx_strlen(dat->hist[dat->n_h_t]);
        dat->cur = (dat->cur) + 1 >= *a ? *a : (dat->cur) + 1;
        mx_input_clear(dat);
        *flag = 1;
    }
}

static int if_else(char red, int flag, t_data *dat) {
    if (red <= '\x1f') {
        mx_input_clear(dat);
        flag = 1;
    }
    return flag;
}

