#include "../inc/libmx.h"

static char *replace_sub(const char *str, const char *sub,
const char *replace, int *count);

static int compare_string(const char *str,
const char *sub, int l2, int c);

char *mx_replace_substr(const char *str, const char *sub,
const char *replace) {
    int count = -1;
    char *u = NULL;
    char *res = NULL;

    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;
    if (mx_strlen(str) == 0 || mx_strlen(sub) == 0 || mx_strlen(replace) == 0)
        return (char *)str;
    u = replace_sub(str, sub, replace, &count);
    res = mx_strnew(count);
    for (int a = 0; a <= count; a++)
        res[a] = u[a];
    free(u);
    return res;
}


static int compare_string(const char *str,
const char *sub, int l2, int c) {
    int r = 0;

    for (r = 0; r < l2; r++) {
        if (str[c + r] != sub[r])
            r = l2 + 5;
    }
    return r;
}

static char *replace_sub(const char *str, const char *sub,
const char *replace, int *count) {
    int l1 = mx_strlen(str);
    int l2 = mx_strlen(sub);
    int l3 = mx_strlen(replace);
    char *u = (char*)malloc(l1*l3);

    for (int c = 0; c < l1; c++) {
        int r = compare_string(str, sub, l2, c);

        (*count)++;
        u[*count] = str[c];
        if (r == l2) {
            for (r = 0; r<l3; r++)
                u[*count + r] = replace[r];
            (*count) = (*count) + l3 - 1;
            c = c + l2 - 1;
        }
    }
    return u;
}
