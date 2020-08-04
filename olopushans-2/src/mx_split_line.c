 #include "ush.h"

static void split_initial(t_split *s, t_data *dat);

static void split_main(char *str, int *flag, t_split *s, t_data *dat);

static void split_dop(char *str, int flag, t_split *s, t_data *dat);

static char **check_if_tilda(char **tok, int num, t_data *dat);

char **mx_split_line(int *num, char **line, t_data *dat) {
    char *str = mx_strdup(*line);
    t_split *s = (t_split*)malloc(sizeof(t_split));
    int flag = 0;
    char **tok = NULL;

    split_initial(s, dat);
    *line = mx_free(*line);
    split_main(str, &flag, s, dat);
    split_dop(str, flag, s, dat);
    *num = s->n_t;
    *line = s->line;
    tok = s->tok;
    tok = check_if_tilda(tok, *num, dat);
    s = mx_free(s);
    return tok;
}

static void split_initial(t_split *s, t_data *dat) {
    s->line = NULL;
    s->tok = NULL;
    s->temp = NULL;
    s->n = 0;
    s->f_dq = 0;
    s->f_q = 0;
    s->tok = NULL;
    s->n_t = 0;
    dat->fd_zap = 0;
    dat->fd_in = 0;
}

static void split_main(char *str, int *flag, t_split *s, t_data *dat) {
    int res = 0;
    int a = 0;

    for (a = 0; str[a] == ' '; a++);
    s = mx_split_main_dop(str, a, s);
    for (; str[a] != '\0'; a++) {
        if ((res = mx_split_symbols(str, &a, s, dat)) == 1)
            break;
        else if (res == 2)
            continue;
        if ((res = mx_split_files(str, &a, flag, dat)) == 1)
            break;
        else if (res == 2)
            continue;
        if (!(str[a] == '\n' && str[a + 1] == '\0')) {
            s->temp[s->n] = str[a];
            (s->n)++;
        }
    }
}

static void split_dop(char *str, int flag, t_split *s, t_data *dat) {
    str = mx_free(str);
    if (flag || s->f_q || s->f_dq)
        s->tok = mx_free_array(s->tok, s->n_t);
    else if (s->tok && !(dat->fd_zap) && !(dat->fd_in)) {
        s->tok[s->n_t] = s->temp;
        (s->n_t)++;
        s->tok = (char**)realloc(s->tok, (s->n_t + 1) * sizeof(char*));
        s->tok[s->n_t] = NULL;
    }
    else if (s->temp && (dat->fd_zap))
        dat->fd_name_z = s->temp;
    else if (s->temp && (dat->fd_in))
        dat->fd_name_in = s->temp;
    if (s->f_q || s->f_dq)
        write(2, "Odd number of quotes.\n", 22);
}

static char **check_if_tilda(char **tok, int num, t_data *dat) {
    int a = 0;
    int i = 0;
    char *p = NULL;
    char *t =NULL;

    if (!tok)
        return tok;
    for (a = 0; a < num; a++) {
        if (tok[a] ? tok[a][0] == '~' : 0) {
            p = mx_cd_tilda(tok[a], &i, dat);
            if (p) {
                if ((t = mx_memchr(tok[a], '/',mx_strlen(tok[a]))) != NULL) {
                    t = mx_strjoin(p, t);
                    free(p);
                    p = t;
                }
                tok[a] = mx_free(tok[a]);
                tok[a] = p;
            }
            else
                for(i=0; tok[a][i] != '\0' && (tok[a][i] == '~' || tok[a][i] == '+'
                    || tok[a][i] == '-'); i++)
                    tok[a][i] = ' ';
        }
    }
    return tok;
}
