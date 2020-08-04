#include "ush.h"

static int echo_dop1(int *a, int *fE, int *fe, char **str);

static void echo_dop2(int *f, char **str, t_data *dat);

static void echo_dop3(int a, int *f, char **str);

static void if_white_back(char str, t_data *dat);

int mx_echo(char **str, int num, t_data *dat) {
    int f[5] = {1, 0, 1, 0, 0};
    int a = 0;
    int flag = 0;
    
    if (!str || num == 1) {
        write(dat->fd[1], "\n", 1);
        return 0;
    }
    for (a = 1; a < num && str[a][0] == '-'; a ++) {
        flag = echo_dop1(&a, &f[1], &f[0], str);
        if (flag != 0)
            break;
        echo_dop3(a, f, str);
    }
    f[3] = a;
    f[4] = num;
    echo_dop2(f, str, dat);
    return flag;
}

static void echo_dop3(int a, int *f, char **str) {
    int b = 0;

    for (b = 0; b < mx_strlen(str[a]); b++) {
        f[0] = str[a][b] == 'e' ? 1 : f[0];
        f[1] = str[a][b] == 'E' ? 1 : f[1];
        f[2] = str[a][b] == 'n' ? 0 : f[2];
    }
}

static void echo_dop2(int *f, char **str, t_data *dat) {
    int a = f[3];
    int b = 0;
    int l_s = -1;
    int num = f[4];

    for (; a < num; a++) {
        for (b = 0; b < mx_strlen(str[a]); b++) {
            if (f[1] && isspace(str[a][b]) && str[a][b] != ' ') {
                if_white_back(str[a][b], dat);
                continue;
            }
            if (str[a][b] == '\n' && !f[2])
                continue;
            l_s = str[a][b] != '\a' ? str[a][b] : l_s;
            write(dat->fd[1], &str[a][b], 1);
        }
        if (a < num - 1)
            write(dat->fd[1], " ", 1);
    }
    if (l_s == -1 && !f[2])
        return;
    b = dat->child == 0 && ((dat->satty == 0 && f[2]) || (dat->satty != 0));
    l_s != '\n' && b ? write(dat->fd[1], "\n", 1) : 0;
}

static int echo_dop1(int *a, int *fE, int *fe, char **str) {
    int b = 0;
    int flag = 0;

    for (b = 1; b < mx_strlen(str[*a]); b++) {
        if (str[*a][b] != 'e' && str[*a][b] != 'n' && str[*a][b] != 'E') {
            flag = 1;
            *fE = *fE && !(*fe) ? 1 : 0;
            *fe = !(*fE);
            *a = mx_strlen(str[*a]) == 1 ? *a : (*a) + 1;
            break;
        }
    }
    return flag;
}

static void if_white_back(char str, t_data *dat) {
    int res = 0;

    res = str == '\n' ? write(dat->fd[0], "\\n", 2) : 0;
    res = str == '\b' ? write(dat->fd[0], "\\b", 2) : 0;
    res = str == '\t' ? write(dat->fd[0], "\\t", 2) : 0;
    res = str == '\a' ? write(dat->fd[0], "\\a", 2) : 0;
    res = str == '\v' ? write(dat->fd[0], "\\v", 2) : 0;
    res = str == '\f' ? write(dat->fd[0], "\\f", 2) : 0;
    res = str == '\r' ? write(dat->fd[0], "\\r", 2) : 0;
    res = str == '\\' ? write(dat->fd[0], "\\", 2) : 0;
}
