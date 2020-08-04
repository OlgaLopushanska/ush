#include "ush.h"

void mx_sig_pause(int sig) {
    sig = 0;
    raise(SIGCONT);
}
