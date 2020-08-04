#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *u = NULL;

    if (list == NULL)
        return;
    u = mx_create_node(data);
    if (!u)
        return;
    u -> data = data;
    u -> next = *list;
    *list = u;
}

