#include "ush.h"

void *mx_free(void *arr) {
    if (arr)
        free(arr);
    arr = NULL;
    return arr;
}
