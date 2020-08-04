#include "../inc/libmx.h"

static char* str_move_left(char* in, int *r, char **lineptr, int len);

static char *init_yoyo(char *yo, char **bufer, int delet, size_t size);

static int read_file_to_line(const int fd, size_t buf_size,
char **yoyo, char **lineptr);

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *yoyo = NULL;
    int s = yoyo ? mx_strlen(yoyo) : buf_size;
    int size = yoyo && s > 0 ? s : buf_size;

    if (fd < 0)
        return -2;
    if (*lineptr) 
        free(*lineptr);
    if (!yoyo) {
        yoyo = mx_strnew(buf_size);
        if (read(fd, yoyo, buf_size) == 0) {
            *lineptr = mx_strnew(1);
            return -1;
        }
    }
    *lineptr = NULL;
    yoyo = (char*)init_yoyo(yoyo, lineptr, s > 0 ? 0 : size, size);
    **lineptr = delim;
    return read_file_to_line(fd, buf_size, &yoyo, lineptr);
}

static char *str_move_left(char* in, int *r, char **lineptr, int len) {
    int a = 0;
    char *buf = NULL;

    (*r)++;
    for (a = 0; in[*r] != '\0'; a++) {
        in[a] = in[*r];
        (*r)++;
    }
    in[a] = '\0';
    *r = -5;
    buf = mx_strnew(len > 0 ? len : 1);
    for (a = 0; a < len; a++)
        buf[a] = (*lineptr)[a];
    free(*lineptr);
    *lineptr = buf;
    return in;
}

static char *init_yoyo(char *yo, char **lineptr, int delet, size_t buf_size) {
    char *buf_t = NULL;

    if (yo && delet) {
        free(yo);
        yo = NULL;
    }
    if (!yo)
        yo = mx_strnew(buf_size);
    if (!(*lineptr))
        *lineptr = mx_strnew(buf_size);
    else {
        buf_t = mx_strnew(delet + buf_size);
        buf_t = mx_memcpy (buf_t, *lineptr, delet);
        free(*lineptr);
        *lineptr = buf_t;
    }
    return yo;
}

static int read_file_to_line(const int fd,
size_t buf_size, char **yoyo, char **lineptr) {
    int pos = -1;
    char delim = **lineptr;
    int size = *yoyo ? mx_strlen(*yoyo) : buf_size;

    **lineptr = '\0';
    for (int a = 0; pos++ != -5 ; a++) {
        if ((*yoyo)[pos] == '\0') {
            *yoyo = (char*)init_yoyo(*yoyo, lineptr, a, buf_size);
            size=read(fd, *yoyo, buf_size);
            pos = 0;
        }
        (*lineptr)[a] = (*yoyo)[pos] != delim ? (*yoyo)[pos] : '\0';
        if ((*yoyo)[pos] == delim || size == 0) {
            *yoyo = str_move_left(*yoyo, &pos, lineptr, a);
            return size == 0 && a == 0 ? -1 : a;
        }
    }
    return 0;
}
