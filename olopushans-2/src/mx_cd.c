#include "ush.h"

static int cd_dop(char *p, int *f, int a, t_data *dat);

int mx_cd(char **str, int num, t_data *dat) {
    char *p = NULL;
    int f[2] = {0,0};
    struct stat u;

    p = mx_cd_get_path(str, num, f, dat);
    dat->flag = dat->flag == -1 ? 1 : 0;
    if (f[1] && p) {
        lstat(p, &u);
        if ((u.st_mode & MX_IFMT) == MX_IFLNK) {
            write(2, "cd: no such file or directory: ", 31);
            write(2, p, mx_strlen(p));
            write(2, "\n", 1);
            dat->flag = 1;
        }
    }
    dat->flag = cd_dop(p, f, 0, dat);
    return dat->flag;
}

static int cd_dop(char *p, int *f, int a, t_data *dat) {
    if (!(dat->flag) && p) {
        dat->flag = chdir(p);
        if (!dat->flag) {
            if (f[0]) {
                free(p);
                p = getwd(NULL);
            }
            if ((a = mx_strlen(p)) > 1)
                p[a - 1] = p[a - 1] == '/' ? '\0' : p[a - 1];
            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", p, 1);
        }
        else if (dat->flag == -1 && p) {
            write(2, "ush: no such file or directory:", 31);
            write(2, p, mx_strlen(p));
            write(2, "\n", 1);
        }
    }
    p = mx_free(p);
    return dat->flag;
}
