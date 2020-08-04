#include "ush.h"

char** mx_free_array(char **arr, int row) {
    if (arr) {
        for (int a = 0; a < row; a++) {
            if (arr[a]) {
                free(arr[a]);
                arr[a] = NULL;
            }
        }
        free(arr);
        arr = NULL;
    }
    return arr;
}
