#include "ush.h"

void mx_signals(int in) {
    in == 1 ? signal(SIGINT, SIG_DFL) : signal(SIGINT, SIG_IGN);
}
