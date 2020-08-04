#include "ush.h"

void mx_sig_exit(int sig) {
    if (sig == SIGINT)
        exit(1);
}
