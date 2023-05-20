/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response.h"

char *construct_response_line(struct response_line *response_line) {
    /*
     * HTTP-Version SP Status-Code SP Reason-Phrase CRLF
     * Example:
     *   GET /path/to/file/index.html HTTP/1.0
     */

    size_t response_length = 0;

    char *raw_http_version = construct_version(response_line->version);
    response_length += strlen(raw_http_version); // HTTP-Version

    response_length += 1; // SP
    response_length += 3; // Status Code

    response_length += 1;                             // SP
    response_length += strlen(response_line->reason); // Reason-Phrase

    //response_length += 1; // CRLF
    response_length += 1; // '/0'

    char *raw_response_line = (char *)malloc(response_length * sizeof(char));
    if (sprintf(raw_response_line, "%s %d %s", raw_http_version,
                response_line->status_code,
                response_line->reason) != response_length - 1) {
        free(raw_response_line);
        return NULL;
    }
    return raw_response_line;
}