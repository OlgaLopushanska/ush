#include "ush.h"

static int insert_global(char **str, int c, char *tok);

void mx_local_value_in2(t_data *dat, char **str, int c, char *tok) {
    int b = 0;

    if (insert_global(str, c, tok) == 0)
        return;
    for (b = 0; b < dat->n_val[0]; b++) {
        if (strcmp(*str, dat->st_val_c[b][0]) == 0) {
            free(dat->st_val_c[b][1]);
            dat->st_val_c[b][0] = mx_strdup(&tok[c + 1]);
            str = mx_free(str);
            continue;
        }
    }
    dat->st_val_c = (char***)realloc(dat->st_val_c, sizeof(char**)
        * (dat->n_val[0] + 1));
    (dat->st_val_c)[dat->n_val[0]] = (char**)malloc(sizeof(char*) * 2);
    (dat->st_val_c)[dat->n_val[0]][0] = mx_strdup(*str);
    (dat->st_val_c[dat->n_val[0]][1])= mx_strdup(&tok[c + 1]);
    (dat->n_val[0])++;
}

static int insert_global(char **str, int c, char *tok) {
    char *temp = NULL;

    temp = getenv(*str);
    if (temp) {
        setenv(*str, &tok[c + 1], 1);
        *str = mx_free(*str);
        return 0;
    }
    return -1;
}
