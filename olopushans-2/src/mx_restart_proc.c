#include "ush.h"

void mx_restart_proc(int pid, int *flag, int n, t_data *dat) {
    int a = 0;

    signal(SIGTSTP, &mx_sig_pause);
    kill(pid, SIGCONT);
    mx_signals(0);
    waitpid(pid, flag, 0x00000002);
    mx_signals(1);
    if (kill(pid, 0) == -1) {
        dat->signals[n] = mx_free(dat->signals[n]);
        for (a = n; a < dat->sigi[0]; a++) {
            dat->sigi[a] = dat->sigi[a + 1];
            dat->signals[a] =  dat->signals[a + 1];
        }
        dat->sigi[dat->sigi[0]] = 0;
        dat->signals[dat->sigi[0]] = NULL;
        (dat->sigi[0])--;
    }
}
