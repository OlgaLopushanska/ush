#include "ush.h"

int *mx_init_int(int value, int num) {
    int a = 0;
    int *arr = NULL;

    arr = (int*)malloc(sizeof(int) * num);
    for (a = 0; a < num; a++) {
        arr[a] = value;
    }
    return arr;
}
