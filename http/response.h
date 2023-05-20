/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_RESPONSE_H
#define SIMPLE_SERVER_RESPONSE_H

#include "message.h"

struct response_line {
    enum Version version;
    int status_code;
    char *reason;
};

char *construct_response_line(struct response_line *);

#endif // SIMPLE_SERVER_RESPONSE_H
