#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    char *u = NULL;

    if (s1 == NULL && s2 == NULL)
        u = NULL;
    else {
        int length1 = 0;
        int length2 = 0;
        
        if (s1 != NULL) 
            length1 = mx_strlen(s1);
        if (s2 != NULL) 
            length2 = mx_strlen(s2);
        u = mx_strnew(length1 + length2);
        for (int a = 0; a < length1; a++)
            u[a] = s1[a];
        for (int a = 0; a < length2; a++)
            u[a + length1] = s2[a];
    }
    return u;
}

