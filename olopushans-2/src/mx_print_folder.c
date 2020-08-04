#include "ush.h"

 void mx_print_folder(t_data *dat) {
    char *path = NULL;
    char *path2 = NULL;
    char *home = getenv("HOME");
    char p[PATH_MAX + 1];
    int a = 0;

    path = getenv("PWD") ? mx_strdup(getenv("PWD")) : getcwd(NULL, 0);
    if (!realpath(path, p)) {
        path = mx_free(path);
        path = getwd(NULL);
    }
    a = mx_strlen(path) - 1;
    /*if(a > 1)
        path[a] = path[a] == '/' ? '\0' : path[a];*/
    if (home)
        if (mx_strcmp(path, home) == 0) {
            path = mx_free(path);
            path = mx_strdup("~");
        }
    path2 = mx_memrchr(path, '/', mx_strlen(path));
    if (path2 && ((path2 + 1) ? *(path2 + 1) != '\0' : 0))
        dat->b = dat->b + write(1, &path2[1], mx_strlen(&path2[1]));
    else 
        dat->b = dat->b + write(1, path, mx_strlen(path));
    path = mx_free(path);
}
