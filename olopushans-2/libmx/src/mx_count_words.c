#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    int count = 0;

    if (str == NULL)
        return -1;
    if(str[0] == '\0')
        return 0;
    for (int a = 1; str[a] != '\0'; a++)
            if (str[a] == c || str[a + 1] =='\0')
                if (str[a - 1] != c || (str[a] != c && str[a + 1] == '\0'))
                    count++;
    return count;
}
