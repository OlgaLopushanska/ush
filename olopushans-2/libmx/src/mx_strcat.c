#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int length1 = mx_strlen(s1);
    int length2 = mx_strlen(s2);

    for (int a = 0; a < length2; a++)
        s1[a + length1] = s2[a];
    s1[length1 + length2] = '\0';
    return s1;
}
