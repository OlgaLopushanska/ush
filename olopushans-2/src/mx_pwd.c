#include "ush.h"

static int pwd_dop(char **tokens, char *terr, int num, int *fL);

int mx_pwd(char **tokens, int num, t_data *dat) {
    int flag = 0;
    char *path = NULL;
    int fL = 1;
    char terr[3] = {'-', ' ', '\n'};
    char p[PATH_MAX + 1];
    
    flag = pwd_dop(tokens, terr, num, &fL);
    if (flag == 2) {
        write(2, "pwd: bad option: ", 17);
        write(2, &terr, 3);
        flag = 1;
    }
    if (flag == 1)
        write(2, "pwd: too many arguments\n", 24);
    else {
        path = getenv("PWD");
        if (fL == 1 && realpath(path, p))
            write(dat->fd[1], path, mx_strlen(path));
        else {
            path = getwd(NULL);
            write(dat->fd[1], path, mx_strlen(path));
            path = mx_free(path);
        }
        write(dat->fd[1], "\n", 1);
    }
    return flag;
}

static int pwd_dop(char **tokens, char *terr, int num, int *fL) {
    int flag = 0;
    int a = 0;
    int b = 0;

    if (num > 1)
        for (b = 1; b < num && flag == 0 && tokens[b]; b++) {
            if (tokens[b][0] != '-')
                return 1;
            for (a = 1; a < mx_strlen(tokens[b]); a++) {
                if (tokens[b][a] != 'L' && tokens[b][a] != 'P') {
                    flag = 2;
                    terr[1] = tokens[b][a];
                    break;
                }
                if (tokens[b][a] == 'L')
                    *fL = 1;
                if (tokens[b][a] == 'P')
                    *fL = 0;
            }
        }
    return flag;
}
