#include "ush.h"

char *mx_check_path(char *path, int i) {
    char p[PATH_MAX + 1];
    char *p2 = NULL;

    if (i == 0 || i == 2)
        if (!realpath(path, p)) {
            path = mx_free(path);
            if (i == 2)
                path = getwd(NULL);
        }
    if (i == 1) {
        p2 = getwd(NULL);
        setenv("PWD", p2, 1);
        setenv("OLDPWD", p2, 1);
        p2 = mx_free(p2);
    }
    if (i == 3)
        path = getenv("PWD") ? mx_check_path(mx_strdup(getenv("PWD")), 2) :
            getwd(NULL);
    return path;
}
