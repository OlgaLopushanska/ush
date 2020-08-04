#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int u = 0;
    int priznak = 0;

    if (str == NULL || sub == NULL)
        u = - 1;
    else {
        for (int a = 0; str[a] != '\0'; a++) {
            priznak = 0;
            if (str[a] == sub[0]) {
                for (int b = 0; sub[b] != '\0'; b++)
                    if (str[a + b] != sub[b])
                        priznak = 1;
                if (priznak == 0)
                    u++;
                priznak = 0;
            }
        }
    }
    return u;
}



