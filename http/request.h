/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_REQUEST_H
#define SIMPLE_SERVER_REQUEST_H

#include <string.h>

#include "message.h"

enum Method { GET, POST, PUT, DELETE, METHOD_NULL };

struct request_line {
    enum Method method;
    char *uri;
    enum Version version;
};

static inline enum Method parse_method(char *raw_method) {
    if (!strcmp(raw_method, "GET")) {
        return GET;
    } else if (!strcmp(raw_method, "POST")) {
        return POST;
    } else if (!strcmp(raw_method, "PUT")) {
        return PUT;
    } else if (!strcmp(raw_method, "DELETE")) {
        return DELETE;
    } else {
        return METHOD_NULL;
    }
}

bool request_line_parser(struct request_line *, struct http_message *);

#endif // SIMPLE_SERVER_REQUEST_H
