#include "ush.h"

int mx_builtin_command(char **token, t_data *dat) {
    int flag = 0;
    
    flag = execvp(token[0], token);
    if (flag == -1) {
        flag = 1;
        write (2, "ush: command not found: ", 24);
        write(2, token[0], mx_strlen(token[0]));
        write(2, "\n", 1);
        flag = 1;
    }
    dat->exi_t = flag;
    return flag;
}
