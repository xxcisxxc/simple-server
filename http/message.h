/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_MESSAGE_H
#define SIMPLE_SERVER_MESSAGE_H

#include "utils/list.h"
#include <string.h>
#include <stdbool.h>

struct start_line {};

struct header_field {
    char *field_name;
    char *field_value;
    struct list list_head;
};

struct message_body {
    char *body;
};

struct http_message {
    struct start_line *start_line;
    struct header_field header_field_list;
    struct message_body message_body;
};

static inline void init_http_message(struct http_message *http_message) {
    init_list_head(&http_message->header_field_list.list_head);
}

bool http_message_parser(struct http_message *, char *);

enum Version { HTTP_1_0, HTTP_1_1, HTTP_NULL };

static inline enum Version parse_version(char *raw_version) {
    if (!strcmp(raw_version, "HTTP/1.1")) {
        return HTTP_1_1;
    } else if (!strcmp(raw_version, "HTTP/1.0")) {
        return HTTP_1_0;
    } else {
        return HTTP_NULL;
    }
}

static inline char *construct_version(enum Version version) {
    switch (version) {
    case HTTP_1_1:
        return "HTTP/1.1";
    case HTTP_1_0:
        return "HTTP/1.0";
    default:
        return NULL;
    }
}

#endif // SIMPLE_SERVER_MESSAGE_H
