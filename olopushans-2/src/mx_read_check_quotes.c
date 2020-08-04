#include "ush.h"

static int quote_1(int b, int log, t_data *dat);

static int quote_2(int b, int log, t_data *dat);

static int quote_3(int b, int log, t_data *dat);

static int quote_5(char *str, int *a, int *out, t_data *dat);

int mx_read_check_quotes(char **res, int *out, t_data *dat) {
    int a = 0;
    int b = 0;
    int buf = 0;
    char *str = NULL;

    str = mx_strdup(&(dat->hist[dat->n_h_t][dat->c_b]));
    if ((buf = mx_strlen(&(dat->hist[dat->n_h_t][dat->c_b]))) == 0)
        return buf;
    for (a = 0; a < buf; a++) {
        if (quote_5(str, &a, out, dat) == -2)
            continue;
        if (*out == -1)
            break;
    }
    if (*out >= 0) {
        for (b = 0, a = 0; b < MX_NUM_SPEC2; a = a + dat->delim[b], b++);
        *out = a ? 1 : 0;
        a = mx_strlen(str);
        *res = *res ? realloc(*res,sizeof(char)
            * (mx_strlen(*res) + a + 5)) : mx_strnew(a);
        *res = mx_strcat(*res, str);
        str = mx_free(str);
    }
    return buf;
}

static int quote_1(int b, int log, t_data *dat) {
    if (!(dat->path) && b < MX_NUM_SPEC2) {
        (dat->delim[b])++;
        dat->path = realloc(dat->path, (dat->n + 1) * sizeof(int));
        dat->path[dat->n] = b;
        (dat->n)++;
        return 1;
    }
    else if (dat->path[dat->n - 1] < 3 && log && b < MX_NUM_SPEC2) {
        (dat->delim[b])++;
        dat->path = realloc(dat->path, (dat->n + 1) * sizeof(int));
        dat->path[dat->n] = b;
        (dat->n)++;
        return 1;
    }
    return quote_2(b, log, dat);
}

static int quote_2(int b, int log, t_data *dat) {
    int k = dat->n - 1;

    if (dat->path[k] >= 3 && dat->path[k] <= 4 && log && b < MX_NUM_SPEC2) {
        (dat->delim[b])++;
        dat->path = realloc(dat->path, (dat->n + 1) * sizeof(int));
        dat->path[dat->n] = b;
        (dat->n)++;
        return 1;
    }
    else if (b < 3 ? dat->path[k] < 3 && (dat->delim[b]) : 0) {
        dat->delim[b] = dat->delim[b] - 1 < 0 ? 0 : dat->delim[b] - 1;
        dat->path = realloc(dat->path, (dat->n - 1) * sizeof(int));
        (dat->n)--;
        return 1;
    }
    return quote_3(b, log, dat);
}

static int quote_3(int b, int log, t_data *dat) {
    int k = dat->n - 1;
    int log2 = dat->path[k] == b - MX_NUM_SPEC2;

    if (b >= 5 && dat->path[k] >= 3 && dat->path[k] <= 4 && log2 && log) {
        b = b - MX_NUM_SPEC2;
        dat->delim[b] = dat->delim[b] - 1 < 0 ? 0 : dat->delim[b] - 1;
        dat->path = realloc(dat->path, (dat->n - 1) * sizeof(int));
        (dat->n)--;
        return 1;
    }
    return 0;
}

static int quote_5(char *str, int *a, int *out, t_data *dat) {
    int b = 0;
    int log = 0;

    if (str[*a] == '\\') {
        if (str[(*a) + 1] != '\0')
                (*a)++;
        return -2;
    }
    for (b = 0; b < MX_NUM_SPEC2 * 2; b++) {
        if (str[*a] == (dat->spec2)[b]) {
            log = !(dat->delim[0]) && !(dat->delim[1]) && !(dat->delim[2]);
            if (quote_1(b, log, dat) == 1)
                break;
            mx_quote_4(str, b, out, dat);
            break;
        }
    }
    return 0;
}
