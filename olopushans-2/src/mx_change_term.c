#include "ush.h"

int mx_change_term(int flag, t_data *dat) {
    struct termios tty;

    if (flag ==2)
        tty = dat->old_term;
    else if (flag == 1) {
        tcgetattr(0, &tty);
        tty.c_lflag |= (ISIG| ICANON);
    }
    else if (flag == 0) {
        tcgetattr(0, &tty);
        tty.c_lflag &= ~(ISIG| ICANON);
    }
    tcsetattr(0, TCSADRAIN, &tty);
    return 0;
}
