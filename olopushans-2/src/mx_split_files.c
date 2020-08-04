#include "ush.h"

static int file_outlet(char *str, int *a, int *flag, t_data *dat);

static int file_inlet(char *str, int *a, int *flag, t_data *dat);

int mx_split_files(char *str, int *a, int *flag, t_data *dat) {
    if (str[*a] == '>')
            return file_outlet(str, a, flag, dat);
    if (str[*a] == '<')
        return file_inlet(str, a, flag, dat);
    return 0;
}

static int file_outlet(char *str, int *a, int *flag, t_data *dat) {
    if (!(dat->fd_zap)) {
        dat->fd_zap = 1;
        dat->fd_in = 0;
    }
    if (str[*a + 1] == '>') {
        dat->fd_zap = 2;
        (*a)++;
        if (str[*a + 1] == '>') {
            *flag = 1;
            return 1;
        }
    }
    for (; str[*a + 1] == '\0' || str[*a + 1] == ' '; (*a)++);
    return 2;  
}

static int file_inlet(char *str, int *a, int *flag, t_data *dat) {
    if (!(dat->fd_in)) {
        dat->fd_in = 1; 
        dat->fd_zap = 0;
    }
    else {
        if ((dat->fd_type) > 2) {
            *flag = 1;
            return 1;
        }
    }
    for (; str[*a + 1] == '\0' || str[*a + 1] == ' '; (*a)++);
    return 2;
}
