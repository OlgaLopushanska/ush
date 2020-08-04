#include "../inc/libmx.h"

void mx_foreach(int *arr, int size, void(*f)(int)) {
    for (int a = 0; a < size; a++)
        f(arr[a]);
}

