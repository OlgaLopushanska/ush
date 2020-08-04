#include "ush.h"

void mx_quote_4(char *str, int b, int *out, t_data *dat) {
    if (b - MX_NUM_SPEC2 >= 3 && dat->path[dat->n-1] >= 3) {
        str = mx_free(str);
        str = mx_strdup("u$h: syntax error near unexpected token ` '\n");
        str[41] = dat->spec2[b];
        write(2,str,44);
        str = mx_free(str);
        *out = -1;
    }
}
