#include "ush.h"

static int set_nonblock_flag(int desc, int value);

char *mx_file_to_str_edited(const int fd) {
    int bytes;
    int size = 65534;
    char *buf = NULL;

    if (fd < 0)
        return NULL;
    buf = mx_strnew(size);
    set_nonblock_flag(fd, 1);
    bytes = read(fd, buf, size);
    if (bytes <= 0)
        buf = mx_free(buf);
    else {
        buf = (char*)realloc(buf, ((bytes) + 5) * sizeof(char));
        buf[bytes] = '\0';
    }
    if (bytes >=1)
        buf[bytes - 1] = buf[bytes - 1] == '\n' ? '\0' : buf[bytes - 1];
    return buf;
}

static int set_nonblock_flag(int fd, int enable) {
    int flags = fcntl (fd, F_GETFL);

    if (flags < 0)
        return flags;
    if (enable != 0)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;
    return fcntl (fd, F_SETFL, flags);
}
