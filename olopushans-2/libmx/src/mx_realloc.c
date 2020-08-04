#include "../inc/libmx.h"

static char *realloc_dop(unsigned long len, size_t size, char *w, void *ptr);

void *mx_realloc(void *ptr, size_t size) {
    char *p = NULL;
    char *w = NULL;
    unsigned long len = 0;

    if (!ptr && size != 0) {
        p = (char*)malloc(size);
        return p;
    }
    if (size == 0) {
        free(ptr);
        ptr = NULL;
        return malloc(0);
    }
    len = mx_strlen((char*)ptr);
    if(size > len)
        w = mx_strnew(size);
    else 
        w = mx_strnew(len);
    w = realloc_dop(len, size, w, ptr);
    return w;
}


static char *realloc_dop(unsigned long len, size_t size, char *w, void *ptr) {   
    if(len >= size)
        mx_memmove(w, ptr, size);
    if(len < size)
        mx_memmove(w, ptr, len);
    free(ptr);
    ptr = NULL;
    return w;
}
