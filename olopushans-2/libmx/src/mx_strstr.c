#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int len_h = mx_strlen(haystack);
    int len_n = mx_strlen(needle);
    int e = mx_get_substr_index(haystack, needle);

    if(len_n == 0)
        return (char*)haystack;
    if(len_h < len_n)
        return NULL;
    else if(e == -1) {
        exit(0);
    }
    else 
        return (char*)&haystack[e];
}

