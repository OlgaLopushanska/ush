#include "ush.h"

static int env_flags(char **str, int num, t_data *dat);

static int env_select_flags(char **str, int *a, int num, int *fl);

static void env_path(char **str, int *a, char *path, int num);

int mx_env(char **str, int num, t_data *dat) {
    char **ep = NULL;

    if (num == 1) {
        for (ep = environ; *ep != NULL; ep++) {
            write(dat->fd[1], *ep, mx_strlen(*ep));
            write(dat->fd[1], "\n", 2);
        }
        return 0;
    }
    return env_flags(str, num, dat);
}

static int env_flags(char **str, int num, t_data *dat) {
    int fl[3] = {0, 0 ,0};
    int flag = 0;
    int a = 0;
    char *path = NULL;
    
    if (env_select_flags(str, &a, num, fl) == 1)
        return 1;
    if (fl[0])
        return mx_env_i(str, a, num, dat);
    if (fl[1]) {
        flag = unsetenv(str[a]);
        mx_env_run(str, num, a + 1, path);
        return 1;
    }
    if (fl[2]) {
        if (num - a >= 2) {
            env_path(str, &a, path, num);
            return 1;
        }
    }
    return flag;
}

static int env_select_flags(char **str, int *a, int num, int *fl) {
    int b = 0;
    
    for (*a = 1; *a < num && str[*a][0] == '-'; (*a)++) {
        for (b = 1; b < mx_strlen(str[*a]); b++)
            if (str[*a][b] != 'i' && str[*a][b] != 'u' && str[*a][b] != 'P') {
                write(2, "env: illegal option -- ", 23);
                write(2, &str[*a][b], 1);
                write(2, "\nusage: env [-iv] [-P utilpath] [-S string]", 43);
                write(2,  " [-u name]            ", 22);
                write(2, "[name=value ...] [utility [argument ...]]\n", 42);
                return 1;;
            }
        for (b = 1; b < mx_strlen(str[*a]); b++) {
            fl[0] = str[*a][b] == 'i' ? 1 : 0;
            fl[1] = str[*a][b] == 'u' ? 1 : 0;
            fl[2] = str[*a][b] == 'P' ? 1 : 0;
        }
    }
    return 0;
}

static void env_path(char **str, int *a, char *path, int num) {
    path = mx_strnew(mx_strlen(str[*a]) + mx_strlen(str[(*a) + 1]) + 100);
    path = mx_strcat(path, str[*a]);
    path = mx_strcat(path, "/");
    path = mx_strcat(path, str[++(*a)]);
    mx_env_run(str, num, *a, path);
    path = mx_free(path);
}

