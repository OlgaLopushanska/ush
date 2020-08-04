#include "ush.h"

int *mx_array_dup(int *arr, int num, int val) {
    int a = 0;
    int *r = NULL;
    
    r = (int*)malloc(sizeof(int) * num);
    for (a = 0; a < num; a++) {
        r[a] = arr ? arr[a] : val;
    }
    return r;
}
