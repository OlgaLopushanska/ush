#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    char *n = NULL;

    if (size < 0) 
        return NULL;
    else {
        n = (char*)malloc(size + 1);
        if(n != NULL)
            for (int a = 0; a <= size; a++)
                n[a] = '\0';
        return n;
    }
}

