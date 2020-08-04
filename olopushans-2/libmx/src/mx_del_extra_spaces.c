#include "../inc/libmx.h"

static int def_white(const char *str, int end, int start);

static char *write_str(const char *str, int end, int r, int start);

char *mx_del_extra_spaces(const char *str) {
    char *u = NULL;

    if (str == NULL)
        u = NULL;
    else {
        int r = 0;
        int sz = mx_strlen(str);
        int end = mx_def_end(str, sz);
        int start = mx_def_start(str, sz);
        
        r = def_white(str, end, start);
        u = write_str(str, end, r, start);
    }
    return u;
}

static int def_white(const char *str, int end, int start) {
    int priznak = 0;
    int r = 0;

    for (int a = start; a <= end; a++) {
        if (mx_isspace(str[a]) == false) {
            r++;
            priznak=1;
        }
        if (mx_isspace(str[a]) == true && priznak == 1) {
            r++;
            priznak = 0;
        }
    }       
    return r;
}


static char *write_str(const char *str, int end, int r, int start) {
    char *u = mx_strnew(r);
    int priznak = 0;
    int t = 0;

    for (int a = start; a <= end; a++) {
         if (mx_isspace(str[a]) == false) {
            u[t++] = str[a];
            priznak=1;
        }
        if (mx_isspace(str[a]) == true && priznak == 1) {
            u[t++] = ' ';
            priznak = 0;
        }
    } 
    return u;
}

