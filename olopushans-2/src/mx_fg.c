#include "ush.h"

static int find_name(char *str, int n, t_data *dat);

static void fg_dop(int num, char **tokens, int *n);

static void change_pid(int *n, char **tokens, t_data *dat, int *pid);

int mx_fg(char **tokens, int num, t_data *dat) {
    int flag; 
    int n = 0;
    int pid = 0;

    if (dat->sigi[0] == 0 && num == 1) {
        write(2, "fg: no current job\n", 19);
        return 1;
    }
    fg_dop(num, tokens, &n);
    change_pid(&n, tokens, dat, &pid);
    if (pid > 0 ? (kill(pid,0) == -1) : 1) {
        write(2, "fg: job not found: ", 19);
        write(2, tokens[1], mx_strlen(tokens[1]));
        write(2, "\n", 1);
        return 1;
    }
    mx_restart_proc(pid, &flag, n, dat);
    return 0;
}

static int find_name(char *str, int n, t_data *dat) {
    int a = 0;
    int b = 0;
    int flag = 0;

    for (a = 1; a <= dat->sigi[0]; a++) {
        flag = 0;
        for (b = 0; dat->signals[b] != '\0'; flag = 0, b++) {
            if (str[b] == dat->signals[a][b])
                flag = 1;
            else {
                flag = 0;
                break;
            }
            if (str[b + 1] == '\0')
                break;
        }
        if (flag) {
            n = a;
            break;
        }
    }
    return n;
}

static void fg_dop(int num, char **tokens, int *n) {
    if (num == 1)
        *n = 1;
    else {
        if (mx_strlen(tokens[1]) <= 0)
            *n = 1;
        else if (tokens[1][0] == '%') {
            if (tokens[1][1] == '\0')
                *n = 1;
            else if (mx_isdigit(tokens[1][1]) == 1)
                *n = -1;
            else if (mx_isalpha(tokens[1][1]) == 1)
                *n = -2;
        }
        else if (mx_isalpha(tokens[1][0]) == 1)
            *n = -3;
        else if (mx_isdigit(tokens[1][0]) == 1)
            *n = -4;
    }
}

static void change_pid(int *n, char **tokens, t_data *dat, int *pid) {
    int a = 0;

    if (*n == -1)
        *n = mx_atoi(&tokens[1][1]);
    else if (*n == - 2)
        *n = find_name(&tokens[1][1], *n, dat);
    else if (*n == -3)
        *n = find_name(tokens[1], *n, dat);
    else if (*n == -4) {
        *pid = mx_atoi(tokens[1]);
        for (a = 1; a <= dat->sigi[0]; a++)
            if (*pid == dat->sigi[a]) {
                *n = a;
                break;
            }
        }
    *pid = *n >= 1 && *n <= dat->sigi[0] ? dat->sigi[*n] : -5;
}
