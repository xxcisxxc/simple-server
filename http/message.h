/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_MESSAGE_H
#define SIMPLE_SERVER_MESSAGE_H

#include "utils/list.h"

struct start_line {};

struct header_field {
    char *field_name;
    char *field_value;
    struct list list;
};

struct message_body {
    char *body;
};

struct http_message {
    struct start_line *start_line;
    struct message_body message_body;
    struct header_field *header_field_list;
};

#endif // SIMPLE_SERVER_MESSAGE_H
