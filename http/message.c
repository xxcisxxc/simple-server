/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "utils/utils.h"

bool header_field_parser(char **, char **, const char *restrict);

/**
 * @brief Parse Incoming HTTP Message
 * @param http_message return parsed http_message structure
 * @param raw_http_message pass raw http message
 */
bool http_message_parser(struct http_message *http_message,
                         char *raw_http_message) {
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
    const char deliminators[] = "\r\n";
    char *current_state, *last_state;

    /* Get Start Line */
    current_state = strtok_r(process_http_message, deliminators, &last_state);
    if (!current_state) {
        goto ERROR;
    }
    http_message->start_line =
        (struct start_line *)malloc_and_strcpy(current_state);

    /* Get Header Lines */
    for (; !strchr(deliminators, last_state[0]);
         current_state = strtok_r(NULL, deliminators, &last_state)) {
        struct header_field *new_header = malloc(sizeof(struct header_field));
        init_list_item(&new_header->list_head, new_header);
        /* parse the header */
        if (!header_field_parser(&new_header->field_name,
                                 &new_header->field_value, current_state)) {
            free(http_message->start_line);
            free_list(&new_header->list_head, true);
            goto ERROR;
        }
        // TODO: Add to list
    }

    /* Get Message Body */
    http_message->message_body.body =
        malloc_and_strcpy(strtok_r(NULL, deliminators, &last_state));

SUCCESS:
    free(process_http_message);
    return true;
ERROR:
    free(process_http_message);
    ERROR_MESSAGE("Internal Server Error: Invalid Header\n");
    return false;
}

bool header_field_parser(char **field_name, char **field_value,
                         const char *restrict raw_header) {
    /*
     * field-line    = field-name ":" OWS field-value OWS
     * OWS: Optional whitespace
     */
    char *process_header = malloc_and_strcpy(raw_header);
    const char deliminators[] = ": ";

    char *current_state, *last_state;
    current_state = strtok_r(process_header, deliminators, &last_state);
    if (!current_state) {
        goto ERROR;
    }
    *field_name = malloc_and_strcpy(current_state);

    current_state = strtok_r(NULL, deliminators, &last_state);
    if (!current_state) {
        free(*field_name);
        goto ERROR;
    }
    *field_value = malloc_and_strcpy(current_state);

    current_state = strtok_r(NULL, deliminators, &last_state);
    if (current_state) {
        free(*field_name);
        free(*field_value);
        goto ERROR;
    }

SUCCESS:
    free(process_header);
    return true;
ERROR:
    free(process_header);
    return false;
}