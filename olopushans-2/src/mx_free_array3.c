#include "ush.h"

void ***mx_free_array3(void ***arr, int row, int col) {
    if (arr) {
        for (int a = 0; a < row; a++) {
            if (arr[a]) {
                for (int b = 0; b < col; b++) {
                    if (arr[a][b]) {
                        free(arr[a][b]);
                        arr[a][b] = NULL;
                    }
                }
                free(arr[a]);
                arr[a] = NULL;
            }
        }
        free(arr);
        arr = NULL;
    }
    return arr;
}
