/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <threads.h>
#include <setjmp.h>

#include "message.h"

thread_local jmp_buf status_jmp_buffer;

void __header_field_parser(char *, char *, const char *restrict);

inline char *malloc_and_strcpy(const char *restrict src) {
    char *dst = malloc(strlen(src));
    return strcpy(dst, src);
}

/**
 * @brief Parse Incoming HTTP Message
 * @param http_message return parsed http_message structure
 * @param raw_http_message pass raw http message
 */
bool http_message_parser(struct http_message *http_message,
                        char *raw_http_message) {
    int return_status; // TODO: Enumerate return status
    /*
     * HTTP-message    = start-line \r\n
     *                   *( header-field \r\n )
     *                   \r\n
     *                   [ message-body ]
     */

    /* Malloc processing message space and copy */
    // because strtok will modify source string
    char *process_http_message = malloc_and_strcpy(raw_http_message);

    /* Split message by \r\n */
    // "strtok_r" is POSIX standard
    const char deliminators [] = "\r\n";
    char *current_state, *last_state;

    /* Get Start Line */
    current_state = strtok_r(process_http_message, deliminators, &last_state);
    if (!current_state) {
        // TODO: Return Status
        goto ERROR;
    }
    http_message->start_line = (struct start_line *)malloc_and_strcpy(current_state);

    /* Get Header Lines */
    for (; !strchr(deliminators, last_state[0]);
         current_state = strtok_r(NULL, deliminators, &last_state)) {
        struct header_field *new_header = malloc(sizeof(struct header_field));
        init_list(&(new_header->list), new_header);
        // TODO: parse the header
        header_field_parser(new_header->field_name, new_header->field_value, current_state);
    }

    /* Get Message Body */
    http_message->message_body.body = malloc_and_strcpy(strtok_r(NULL, deliminators, &last_state));

SUCCESS:
    return true;
ERROR:
    // remember to free before jump
    return false;
}

void __header_field_parser(char *field_name, char *field_value, const char * restrict raw_header) {
    /*
     * field-line    = field-name ":" OWS field-value OWS
     * OWS: Optional whitespace
     */
    char *process_header = malloc_and_strcpy(raw_header);
    const char deliminators [] = ": ";

    char *current_state, *last_state;
    current_state = strtok_r(process_header, deliminators, &last_state);
    if (!current_state) {
        // setjmp
        goto ERROR;
    }
    field_name = malloc_and_strcpy(current_state);

    current_state = strtok_r(NULL, deliminators, &last_state);
    if (!current_state) {
        goto ERROR;
    }
    field_value = malloc_and_strcpy(current_state);

    current_state = strtok_r(NULL, deliminators, &last_state);
    if (current_state) {
        goto ERROR;
    }
ERROR:
    return;
}