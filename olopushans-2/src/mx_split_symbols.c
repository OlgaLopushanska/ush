#include "ush.h"

static int split1(char *str, int *a, t_split *s, t_data *dat);

static int split2(char *str, int *a, t_split *s, t_data *dat);

static int split3(char *str, int *a, t_split *s, t_data *dat);

static char **if_space(char **tok, int *n_t, char **temp, char *str);

static int space_if (char *str, int *a, t_split *s, t_data *dat);

int mx_split_symbols(char *str, int *a, t_split *s, t_data *dat) {
    int k = 0;

    k = s->f_q == 0 && !(dat->fd_zap) && !(dat->fd_in);
    if (str[*a] == ';' && s->f_dq == 0 && k) {
        s->line = mx_strdup(&str[*a + 1]);
        if (s->n_t == 0 && mx_strlen(s->temp) == 0)
            s->tok = mx_free_array(s->tok, s->n_t);
        return 1;
    }
    if (str[*a] == '\\') { 
        *a = mx_if_escape(str, *a, s);
        s->temp[s->n] = str[*a];
        (s->n)++;
        return 2;
    }
    return split1(str, a, s, dat);
}

static int split1(char *str, int *a, t_split *s, t_data *dat) {
    if ((str[*a] == ' ' || str[*a] == '>' || str[*a] == '<') && s->f_dq == 0 && s->f_q == 0)
        return space_if (str, a, s, dat);
    if (str[*a] == '"' && s->f_q == 0) {
        s->f_dq = s->f_dq ? 0 : 1;
        return 2;
    }
    if (str[*a] == '\'' && s->f_dq == 0) {
        s->f_q = s->f_q ? 0 : 1;
        return 2;
    }
    return split2(str, a, s, dat);
}

static int space_if (char *str, int *a, t_split *s, t_data *dat) {
    int b = 0;
    
    for (b = *a; str[b] == ' '; b++);
    if (str[b] == '\0' || str[b] == ';') {
        *a = b - 1;
        return 2;
    }
    if (str[b] == '>' || str[b] == '<')
        *a = b;
    if (s->temp && (dat->fd_zap))
        dat->fd_name_z = s->temp;
    else if (s->temp && (dat->fd_in))
        dat->fd_name_in = s->temp;
    s->tok = if_space(s->tok, &(s->n_t), &(s->temp), str);
    s->n = 0;
    if (str[*a] == '>' || str[*a] == '<')
        return 0;
    return 2;
}

static int split2(char *str, int *a, t_split *s, t_data *dat) {
    char *doch = NULL;
    char *temp2 = NULL;
    int end_sign = 0;
    
    if (str[*a] == '`' || (str[*a] == '$' && s->f_q == 0)) {
        doch = mx_run_doch(&str[*a], &(dat->flag), &end_sign, dat);
        if (doch) {
            temp2 = mx_strnew(mx_strlen(str) + mx_strlen(s->temp)
                + mx_strlen(doch));
            temp2 = mx_strcat(temp2, s->temp);
            temp2 = mx_strcat(temp2, doch);
            s->temp = mx_free(s->temp);
            doch = mx_free(doch);
            s->temp = temp2;
            s->n = mx_strlen(s->temp);
            *a = *a + end_sign;
            return 2;
        }
        else {
            dat->flag = 1;
            return 1;
        }
    }
    return split3(str, a, s, dat);
}

static int split3(char *str, int *a, t_split *s, t_data *dat) {
    char *doch = NULL;
    int end_sign = 0;

    if (str[*a] == '(' && *a == 0) {
        doch = mx_run_doch(&str[*a], &(dat->flag), &end_sign, dat);
        doch = mx_free(doch);
        s->tok = mx_free_array(s->tok, s->n_t);
        return 1;
    }
    return 0;
}

static char **if_space(char **tok, int *n_t, char **temp, char *str) {
    tok[*n_t] = *temp;
    (*n_t)++;
    tok = (char**)realloc(tok, (*n_t + 1) * sizeof(char*));
    tok[*n_t] = NULL;
    *temp = mx_strnew(mx_strlen(str));
    return tok;
}
