#include "ush.h"

static void local_value_in_dop1(char **tok, int num, int *err);

static int local_value_in_dop2(char *tok, int err);

int mx_local_value_in(char **tok, int num, t_data *dat) {
    int a = 0;
    int c = 0;
    char *str = NULL;
    int err = 0;

    local_value_in_dop1(tok, num, &err);
    if (local_value_in_dop2(tok[num - 1], err) == 127)
        return 127;
    for (a = 0; a < num; a++) {
        c = mx_get_char_index(tok[a], '=');
        str = mx_strndup(tok[a], c);
        mx_local_value_in2(dat, &str, c, tok[a]);
        str = mx_free(str);
    }
    return 0;
}

static void local_value_in_dop1(char **tok, int num, int *err) {
    int a = 0;
    int b = 0;

    for (a = 0; a < num; a++) {
        if (!tok[a])
            *err = 1;
        else if (mx_strlen(tok[a]) == 0 || tok[a][0] == '=')
            *err = 1;
        else if (mx_isdigit(tok[a][0]))
            for (b = 1; tok[a][b] != '='; b++) { 
                *err = mx_isdigit(tok[a][b]) ? *err : 1;
                if (*err) 
                    break;
            }
        else if (mx_isalpha(tok[a][0]) == 0)
            *err = 1;
        if (*err)
            break;
    }
}

static int local_value_in_dop2(char *tok, int err) {
    if (err) { 
        write(2, "zsh: command not found: ", 24);
        write(2, tok, mx_strlen(tok));
        write(2, "\n", 1);
        return 127;
    }
    return 0;
}
