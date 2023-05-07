/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_LIST_H
#define SIMPLE_SERVER_LIST_H

struct list {
    void *data;
    struct list *next;
    struct list *prev;
};

static inline void init_list(struct list *list, void *data) {
    list->next = list;
    list->prev = list;
    list->data = data;
}

#endif // SIMPLE_SERVER_LIST_H
