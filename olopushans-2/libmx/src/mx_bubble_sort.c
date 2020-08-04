#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int y = 0;

    for (int b = 0; b < size; b++) {
        for (int a = 0; a < size - 1; a++) {
            if (mx_strcmp(arr[a], arr[a + 1]) > 0) {
                char *k = arr[a];
                
                arr[a] = arr[a + 1];
                arr[a + 1] = k;
                y++;
            }
        }
    }
    return y;
}

