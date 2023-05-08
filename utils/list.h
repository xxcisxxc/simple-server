/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_LIST_H
#define SIMPLE_SERVER_LIST_H

#include <stdbool.h>
#include <stdlib.h>

/*
 * Doubly Linked List
 *
 * -------------------------------------------------------
 * |                                                     |
 * -->list_head <--> list_item <--> ... <--> list_item <--
 */

struct list {
    void *data;
    struct list *next;
    struct list *prev;
};

static inline void init_list_head(struct list *list_head) {
    list_head->data = NULL;
    list_head->next = list_head;
    list_head->prev = list_head;
}

static inline void init_list_item(struct list *list_item, void *data) {
    list_item->next = list_item;
    list_item->prev = list_item;
    list_item->data = data;
}

static inline void add_list_item_front(struct list *list_head,
                                       struct list *list_item) {
    struct list *first_list_item = list_head->next;
    list_head->next = list_item;
    list_item->prev = list_head;
    first_list_item->prev = list_item;
    list_item->next = first_list_item;
}

static inline void add_list_item_end(struct list *list_head,
                                     struct list *list_item) {
    struct list *last_list_item = list_head->prev;
    list_head->prev = list_item;
    list_item->next = list_head;
    last_list_item->next = list_item;
    list_item->prev = last_list_item;
}

static inline void free_list_item(struct list *list_item, bool is_free) {
    struct list *prev_list_item = list_item->prev,
                *next_list_item = list_item->next;
    prev_list_item->next = next_list_item;
    next_list_item->prev = prev_list_item;
    is_free ? free(list_item->data) : NULL;
}

static inline void free_list(struct list *list_head, bool is_free) {
    struct list *current_list_item, *next_list_item;
    while (list_head->next != list_head) {
        current_list_item = list_head->next;
        next_list_item = current_list_item->next;
        list_head->next = next_list_item;
        next_list_item->prev = list_head;
        is_free ? free(current_list_item->data) : NULL;
    }
}

#endif // SIMPLE_SERVER_LIST_H
