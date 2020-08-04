#include "ush.h"

static int child_builtin(int a, char **token, int num, t_data *dat);

static void child_prepare_files(t_data *dat);

static int master(int proc, char **token, t_data *dat);

static void sig_pause(int sig) {
    if (sig == SIGTSTP)
        raise(SIGCONT);
}

int mx_create_process(int a, char **token, int num, t_data *dat) {
    int flag = 0;
    pid_t proc = 0;

    dat->proc = getpid();
    if (dat->child == 1) {
        proc = fork();
        dat->proc = proc;
    }
    if (proc == 0 )
        flag = child_builtin(a, token, num, dat);
    if (proc >= 0 && dat->child == 1)
        flag = master(proc, token, dat);
    free(((dat->st_val_c)[2][1]));
    (dat->st_val_c)[2][1] = mx_itoa(flag);
    return flag;
}

static int child_builtin(int a, char **token, int num, t_data *dat) {
    int flush = 1;
    int flag = 0;

    child_prepare_files(dat);
    if (a < MX_NUM_COM) {
        flag = mx_swit(a, token, num, dat);
        flush = 0;
    }
    else if (token[0] && flush == 1)
        flag = mx_builtin_command(token, dat);
    if (dat->child == 1)
        exit(flag);
    return flag;
}

static void child_prepare_files(t_data *dat) {
    if (dat->child == 1) {
        if (dat->fd[1] == 1 && dat->fd_name_z) {
            if (dat->fd_zap == 1)
                freopen(dat->fd_name_z, "w", stdout);
            if (dat->fd_zap == 2)
                freopen(dat->fd_name_z, "a", stdout);
        }
        if (dat->fd_in)
            freopen(dat->fd_name_in, "r+", stdin);
        if (dat->fd[1] != 1)
            dup2(dat->fd[1],STDOUT_FILENO);
    }
    else {
        if (dat->fd[1] == 1 && dat->fd_name_z) {
            if (dat->fd_zap == 1)
                dat->fd[1] = open(dat->fd_name_z, O_RDWR | O_TRUNC);
            if (dat->fd_zap == 2)
                dat->fd[1] = open(dat->fd_name_z, O_RDWR | O_APPEND);
        }
    }
}

static int master(int proc, char **token, t_data *dat) {
    int flag = 0;

    signal(SIGTSTP, &sig_pause);
    mx_signals(0);
    waitpid(proc, &flag, 0x00000002);
    usleep(1000);
    if (kill(proc, 0) != -1) {
        (dat->sigi[0])++;
        dat->sigi = (int*)realloc(dat->sigi, sizeof(int) * (dat->sigi[0] + 1));
        dat->sigi[dat->sigi[0]] = proc;
        dat->signals = (char**)realloc(dat->signals, sizeof(char*)
            * (dat->sigi[0] + 1));
        dat->signals[dat->sigi[0]] = mx_strdup(token[0]);
    }
    mx_signals(1);
    return flag;
}
