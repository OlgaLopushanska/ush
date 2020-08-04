#include "ush.h"

static char *path_dop0(char *str, char *p, int *i, int *a);

static char *cd_dop_points(char *p, int *i);

static char *path_init(char *str, char *p);

static char *cd_flags(char *str, int *f, int num, t_data *dat);

char *mx_cd_get_path(char **str, int num, int *f, t_data *dat) {
    char *p = NULL;
    int n = 0;
    int i = 0;
    int a = 0;

    if (num == 1 && getenv("HOME"))
        return mx_strdup(getenv("HOME"));
    dat->flag = 0;
    for (n = 1; n < num && str[n] && dat->flag >= 0; n++) {
        if (str[n][0] == '-') {
            p = cd_flags(str[n], f, num, dat);
            if (dat->flag <= -1)
                return p;
            continue;
        }
        p = path_init(str[n], p);
        if (!p)
            return p;
        for (i = mx_strlen(p), a = 0; str[n][a] != '\0'; a++) {
            p = path_dop0(str[n], p, &i, &a);
        }
    }
    return p;
}

static char *path_dop0(char *str, char *p, int *i, int *a) {
    if (str[*a] == '.' && str[(*a) + 1] == '.') {
        p = cd_dop_points(p, i);
        if (str[(*a) + 2] == '/')
            *a = (*a) + 1;
        else
            *a = (*a) + 1;
    }
    else if (str[*a] == '.' && str[(*a) + 1] != '.') {
        if (str[(*a) + 1] == '/')
            *a = (*a) + 1;
    }
    else {
        p[*i] = str[*a];
        (*i)++;
    }
    return p;
}

static char *cd_dop_points(char *p, int *i) {
    char *temp = NULL;
    int a = mx_strlen(p);

    if (p[a] == '\0' && a > 1)
        p[a - 1] = p[a - 1] == '/' ? '\0' : p[a - 1];
    temp = mx_memrchr(p, '/', mx_strlen(p));
    if (mx_get_substr_index(p, temp) > 0)
        temp[0] = '\0';
    else
        temp[1] = '\0';
    *i = mx_strlen(p);
    return p;
}

static char *path_init(char *str, char *p) {
    char *temp = mx_strnew(PATH_MAX);

    p = mx_free(p);
    if (mx_isalpha(str[0]) || (str[0] == '.')) {
        p = mx_check_path(p, 3);
        temp = mx_strcat(temp, p);
        free(p);
        p = temp;
        if (p[mx_strlen(p) - 1] != '/')
            p = mx_strcat(p, "/");
    }
    if (str[0] == '/') 
        p = mx_strnew(PATH_MAX);
    return p;
}

static char *cd_flags(char *str, int *f, int num, t_data *dat) {
    char *p = NULL;

    if (str[1] != '\0' && (str[1] != 'P' && str[1] != 's')) {
        write(2, "cd: no such file or directory: ", 31);
        write(2, str, mx_strlen(str));
        write(2, "\n", 1);
        dat->flag = -1;
        return p;
    }
    if (str[1] == '\0' && getenv("OLDPWD")) {
        p = mx_check_path(mx_strdup(getenv("OLDPWD")), 0);
        dat->flag = -2;
        return p;
    }
    f[0]  = str[1] == 'P' ? 1 : f[0];
    f[1] = str[1] == 's' ? 1 : f[1];
    if ((f[0] || f[1]) && num == 2) {
        dat->flag = -2;
        if (getenv("HOME"))
            p = mx_check_path(mx_strdup(getenv("HOME")), 0);
    }
    return p;
}
