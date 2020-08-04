#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *d = (char*)s1;
    char *s = (char*)s2;
    unsigned int i = 0;

    if (n == 0)
        return 0;
    while (d[i]!='\0' || s[i]!='\0') {
        if (d[i]!=s[i])
            return (d[i] - s[i]);
        i++;
    }
    return (d[i]-s[i]);
}

