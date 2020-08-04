#include "ush.h"

static int which_dop1(int num, char **str, int *fl, t_data *dat);

static int which_dop2(int flag, int *fl, char *str, t_data *dat);

static int which_dop3(char *str, int *fl, int flag, t_data *dat);

static int which_dop4(char *str, int *fl, char *dir, t_data *dat);

int mx_which(char **str, int num, t_data *dat) {
    int a = 0;
    int res = 0;
    int fl[3] = {1, 0, 0};
    int flag = 0;
    
    a = which_dop1(num, str, fl, dat) ;
    if (dat->flag == 1)
        return 1;
    for (; a < num; a++) {
        flag  = 1;
        if (!(flag = which_dop2(flag, fl, str[a], dat)) && !fl[1])
            continue;
        flag  = which_dop3(str[a], fl, flag, dat);
        res = flag ? 1 : res;
        if (flag  == 1 && !fl[2]) {
            write(2, str[a], mx_strlen(str[a]));
            write(2, " not found\n", 11);
        }
    }
    return res;
}

static int which_dop1(int num, char **str, int *fl, t_data *dat) {
    int a = 0;
    int b = 0;

    if (num <= 1)
        return 1;
    for (a = 1; a < num && str[a][0] == '-'; a++) {
        for (b = 1; str[a][b] != '\0'; b++) {
            if (str[a][b] != 'a' && str[a][b] != 's') {
                write(dat->fd[1], "which: bad option: -", 20);
                write(2, &str[a][b], 1);
                write(2, "\n", 1);
                return 1;
            }
            fl[0] = str[a][b] == 'a' || str[a][b] == 's' ? 0 : 1;
            fl[1] = str[a][b] == 'a' ? 1 : 0;
            fl[2] = str[a][b] == 's' ? 1 : 0;
        }
    } 
    return a;
}

static int which_dop2(int flag, int *fl, char *str, t_data *dat) {
    int b = 0;

    for (b = 0; b < dat->n_reserv && flag; b++)
        if (mx_strcmp(str, dat->reserved[b]) == 0) {
            if (!fl[2]) {
                write(dat->fd[1], str, mx_strlen(str));
                write(dat->fd[1], ": shell reserved word\n", 28);
            }
            flag = 0;
        }
    for (b = 0; b < MX_NUM_COM && flag; b++)
        if (mx_strcmp(str, dat->names[b]) == 0) {
            if (!fl[2]) {
                write(dat->fd[1], str, mx_strlen(str));
                write(dat->fd[1], ": shell built-in command\n", 25);
            }
            flag = 0;
        }
    return flag;
}

static int which_dop3(char *str, int *fl, int flag, t_data *dat) {
    char *temp = NULL;
    int y = 0;
    int r = 0;
    char *dir = NULL;
    int b = 0;
   
    dat->n = 1;
    temp = getenv("PATH");
    for (; r != -1; y = y + r + 1) {
        r = mx_get_char_index(&temp[y], ':');
        dir = mx_strnew(mx_strlen(temp));
        for (b = y; r >= 0 ? b < r + y : temp[b] != '\0'; b++)
            dir[b - y] = temp[b];
        if ((flag = which_dop4(str, fl, dir, dat)) == 1)
            continue;
        dir = mx_free(dir);
        dat->n = flag == 0 ? 0 : dat->n;
        if (flag == 0 && !fl[1])
            break;
    }
    return dat->n;
}

static int which_dop4(char *str, int *fl, char *dir, t_data *dat) {
    DIR *dir1 = NULL;
    struct dirent *dir2;
    int flag = 1;
    
    dir1 = opendir(dir);
    if (!dir1)
        return 1;
    dir2 = readdir(dir1);
    while (dir2 != NULL) {
        if (mx_strcmp(dir2->d_name, str) == 0) {
            if (!fl[2]) {
                write(dat->fd[1], dir, mx_strlen(dir));
                write(1, "/", 1);
                write(1, dir2->d_name, mx_strlen(dir2->d_name));
                write(1, "\n", 1);
            }
            flag = 0;
            break;
        }
        dir2 = readdir(dir1);
    }
    closedir(dir1);
    return flag;
}

