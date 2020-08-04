#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    t_list *p = malloc(sizeof(t_list));

    if (!p) 
        return NULL;
    p -> data = data;
    p -> next = NULL;
    return p;
}

