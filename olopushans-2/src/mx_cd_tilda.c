#include "ush.h"

static char *tilda_dop1(char *str, t_data *dat);

static char *tilda_username(char *str, char *p, t_data *dat);

static char *tilda_username2(char *str, char *p, struct stat u, t_data *dat);

char *mx_cd_tilda(char *str, int *i, t_data *dat) {
    char *p = NULL;

    if ((str[1] == '\0' || str[1] == '/') && getenv("HOME"))
        p = mx_strdup(getenv("HOME"));
    if (mx_isalpha(str[1])) {
        p = tilda_dop1(str, dat);
        if (dat->flag <= -1)
            return p;
    }
    if (str[1] == '-' && getenv("OLDPWD")) {
        p = mx_strdup(getenv("OLDPWD"));
        (*i)++;
    }
    if (str[1] == '+' && getenv("PWD")) {
        p = mx_strdup(getenv("PWD"));
        (*i)++;
    }
    return p;
}

static char *tilda_dop1(char *str, t_data *dat) {
    char *p = NULL;
    char *temp = NULL;
    char *temp2 = NULL;
    int i = 0;

    dat->flag = 0;
    p = mx_strdup(getenv("HOME"));
    temp = mx_memrchr(p, '/', mx_strlen(p));
    temp[0] = '\0';
    i = mx_strlen(p) + mx_strlen(&str[1]) + 100;
    p = (char*)realloc(p, sizeof(char) * i);
    p = mx_strcat(p, "/");
    temp = mx_strdup(str);
    temp2 = mx_memrchr(temp, '/', mx_strlen(temp));
    if (temp2)
        temp2[0] = '\0';
    p = mx_strcat(p, &temp[1]);
    free(temp);
    p = tilda_username(str, p, dat);
    return p;
}

static char *tilda_username(char *str, char *p, t_data *dat) {
    struct stat u;

    dat->flag = lstat(p, &u);
    if (!(dat->flag)) {
        p = tilda_username2(str, p, u, dat);
        if (dat->flag <= -1)
            return p;
    }
    else {
        write(2, "ush: no such file or directory:", 31);
        write(2, str, mx_strlen(str));
        write(2, "\n", 1);
        dat->flag = -1;
        return p;
    }
    return p;
}

static char *tilda_username2(char *str, char *p, struct stat u, t_data *dat) {
    struct passwd *r = NULL;
    char *temp = NULL;

    r = getpwuid(u.st_uid);
    if (r != NULL)
        temp = mx_memrchr(p, '/', mx_strlen(p));
    if (mx_strcmp(&temp[1], r->pw_name) == 0) {
        temp = mx_memchr(str, '/', mx_strlen(str));
        dat->flag = -2;
        return p;
    }
    return p;
}
