#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int u = -1;

    if (str == NULL || sub == NULL) 
        u = -2;
    else {
        for (int a = 0; str[a] != '\0'; a++) {
            int priznak = 0;
            
            if (str[a] == sub[0]) {
                for (int b = 0; sub[b] != '\0'; b++)
                    if (str[a + b] != sub[b])
                        priznak++;
                if (priznak == 0) {
                    u = a;
                    break;
                }
            }
        }
    }
    return u;
}


