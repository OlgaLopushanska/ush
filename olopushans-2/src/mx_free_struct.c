#include "ush.h"

void mx_free_struct(t_data *dat) {
    dat->st_val_c = (char***)mx_free_array3((void*)(dat->st_val_c),
    dat->n_val[0], 2);
    dat->n_val = mx_free(dat->n_val);
    dat->spec = mx_free(dat->spec);
    dat->spec2 = mx_free(dat->spec2);
    dat->wr_spec = mx_free_array(dat->wr_spec, MX_NUM_SPEC2);
    dat->fd = mx_free(dat->fd);
    dat->fd_name_z = mx_free(dat->fd_name_z);
    dat->fd_name_in = mx_free(dat->fd_name_in);
    dat->names = mx_free_array(dat->names, MX_NUM_COM);
    dat->reserved = mx_free_array(dat->reserved, dat->n_reserv);
    dat->hist = mx_free_array(dat->hist, dat->n_h);
    dat->signals = mx_free_array(dat->signals, dat->sigi[0] + 1);
    dat->sigi = mx_free(dat->sigi);
    dat->delim = mx_free(dat->delim);
    dat->path = mx_free(dat->path);
    dat = mx_free(dat);
}
