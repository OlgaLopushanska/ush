#include "ush.h"

char **mx_init_wr_spec(void) {
    char **wr_spec = NULL;

    wr_spec = (char**)malloc(sizeof(char*) * MX_NUM_SPEC2);
    wr_spec[0] = mx_strdup("bquote");
    wr_spec[1] = mx_strdup("quote");
    wr_spec[2] = mx_strdup("dquote");
    wr_spec[3] = mx_strdup("subsh");
    wr_spec[4] = mx_strdup("cursh");
    return wr_spec;
}
