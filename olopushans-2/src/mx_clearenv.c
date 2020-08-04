#include "ush.h"

int mx_clearenv(void) {
    char **env = NULL;
    char **ep = NULL;
    int a = 0;
    int b = 0;

    for (ep = environ, a = 0; *ep != NULL; ep++, a++) {
        env = (char**)realloc(env, sizeof(char*) * (a + 1));
        env[a] = mx_strdup(*ep);
        env[a][mx_get_char_index(env[a], '=')] = '\0';
    }
    for (b = 0; b < a; b++)
        unsetenv(env[b]);
    env = mx_free_array(env, a);
    return 0;
}
