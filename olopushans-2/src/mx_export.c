#include "ush.h"

static int export_dop(int y, char *str, int *cont);

static void export_dop2(char *str, int y);

int mx_export(char **str, int num, t_data *dat) {
    int a = 0;
    char *name = NULL;
    int flag = 0;
    int y = 0;
    int cont = 0;

    dat->flag = 0;
    if (str[1]) {
        for (a = 1; a < num; a++) {
            y = mx_get_char_index(str[a], '=');
            flag = export_dop(y, str[a], &cont);
            if (cont)
                continue;
            export_dop2(str[a], y);
            name = mx_strdup(str[a]);
            name[y] = '\0';
            setenv(name, &str[a][y + 1], 0);
            name = mx_free(name);
        }
    }
    return flag;
}

static int export_dop(int y, char *str, int *cont) {
    int flag = 0;

    *cont = 0;
    if (y <= 0 && mx_strlen(str) == 1) {
        write(2, "ush: bad assignment\n", 20);
        flag = 1;
        *cont = 1;
    }
    else if (y <= 0 && mx_strlen(str) > 1) {
        write(2, "ush: ", 5);
        write(2, &str[1], y - 1);
        write(2, " not found\n", 11);
        flag = 1;
        *cont = 1;
    }
    if (mx_isdigit(str[0])) {
        write(2, "export: not an identifier: ", 27);
        write(2, str, mx_strlen(str));
        write(2, "\n", 1);
        *cont = 1;
    }
    return flag;
}

static void export_dop2(char *str, int y) {
    int b = 0;

    for (b = 0; b < y; b++) {
        if (!mx_isalpha(str[b]) && !mx_isdigit(str[b])) {
            write(2, "export: not valid in this context: ", 35);
            write(2, str, b);
            write(2, "\n", 1);
            break;
        }
    }
}

