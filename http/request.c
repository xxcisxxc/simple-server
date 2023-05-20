/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "utils/utils.h"

bool request_line_parser(struct request_line *request_line, struct http_message *http_message) {
    /*
     * Method SP Request-URI SP HTTP-Version CRLF
     * Example:
     *   GET /path/to/file/index.html HTTP/1.0
     */

    char *raw_request_line = malloc_and_strcpy((char *)http_message->start_line);
    char *current_state, *last_state;

    current_state = strtok_r(raw_request_line, " ", &last_state);
    enum Method method;
    if ((method = parse_method(current_state)) == METHOD_NULL) {
        ERROR_MESSAGE("Wrong Request Method - ");
        goto ERROR;
    }
    request_line->method = method;

    current_state = strtok_r(NULL, " ", &last_state);
    if (!current_state) {
        ERROR_MESSAGE("Invalid Request URI - ");
        goto ERROR;
    }
    request_line->uri = malloc_and_strcpy(current_state);

    current_state = strtok_r(NULL, " ", &last_state);
    enum Version version;
    if ((version = parse_version(current_state)) == HTTP_NULL) {
        ERROR_MESSAGE("Invalid HTTP Version - ");
        free(request_line->uri);
        goto ERROR;
    }
    request_line->version = version;

    if (strtok_r(NULL, " ", &last_state)) {
        ERROR_MESSAGE("Invalid Request Line - ");
        free(request_line->uri);
        goto ERROR;
    }

SUCCESS:
    free(raw_request_line);
    free(http_message->start_line);
    http_message->start_line = (struct start_line *)request_line;
    return true;
ERROR:
    free(raw_request_line);
    ERROR_MESSAGE("Internal Server Error\n");
    return false;
}