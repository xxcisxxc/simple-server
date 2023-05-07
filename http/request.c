/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include <stdlib.h>
#include <string.h>

#include "request.h"

void request_parse_head(struct request *request, char *raw_request,
                        int len_request) {
    /*
     * Method Path Version
     * Example:
     *   GET /path/to/file/index.html HTTP/1.0
     */

    /* Malloc URL space and parse */
    // because strtok will modify source string
    char *request_split = malloc(url_len * sizeof(char));
    request->len_url = len_url;
    request->url = malloc(url_len * sizeof(char));

    strcpy(url_split, url);
    strcpy(request->url, url);

    // "strtok_r" is POSIX standard
    char delim[] = " \t";
    strtok_r(url_split, );
}