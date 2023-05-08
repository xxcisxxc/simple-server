/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

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
        ERROR_MESSAGE("Invalid Start Line - ");
        goto ERROR;
    }
    http_message->start_line =
        (struct start_line *)malloc_and_strcpy(current_state);

    /* Get Header Lines */
    for (; !strchr(deliminators, last_state[0]);
         strtok_r(NULL, deliminators, &last_state)) {
        struct header_field *new_header = malloc(sizeof(struct header_field));
        init_list_item(&new_header->list_head, new_header);
        /* parse the header */
        if (!header_field_parser(&new_header->field_name,
                                 &new_header->field_value, last_state)) {
            free(http_message->start_line);
            free_list(&http_message->header_field_list.list_head, true);
            free(new_header);
            ERROR_MESSAGE("Invalid Header - ");
            goto ERROR;
        }
        /* Add to the linked list */
        add_list_item_end(&http_message->header_field_list.list_head, &new_header->list_head);
    }

    /* Get Message Body */
    if (last_state[0] == '\0') {
        ERROR_MESSAGE("No CRLF After Header - ");
        goto ERROR;
    }
    current_state = strtok_r(NULL, deliminators, &last_state);
    if (current_state) {
        http_message->message_body.body = malloc_and_strcpy(current_state);
    } else {
        http_message->message_body.body = malloc(sizeof(char));
        *http_message->message_body.body = '\0';
    }

SUCCESS:
    free(process_http_message);
    return true;
ERROR:
    free(process_http_message);
    ERROR_MESSAGE("Internal Server Error\n");
    return false;
}

bool header_field_parser(char **field_name, char **field_value,
                         const char *restrict raw_header) {
    /*
     * field-line    = field-name ":" OWS field-value OWS
     * OWS: Optional whitespace
     */
    char *process_header = malloc_and_strcpy(raw_header);
    char deliminators[] = ": \r\n";

    char *current_state, *last_state;
    deliminators[1] = '\0';
    current_state = strtok_r(process_header, deliminators, &last_state);
    if (!current_state) {
        ERROR_MESSAGE("No Separator \':\' or No Field Name - ");
        goto ERROR;
    }
    *field_name = malloc_and_strcpy(current_state);

    deliminators[1] = ' ';
    current_state = strtok_r(NULL, deliminators + 1, &last_state);
    if (!current_state) {
        free(*field_name);
        ERROR_MESSAGE("Invalid Field Value - ");
        goto ERROR;
    }
    *field_value = malloc_and_strcpy(current_state);

SUCCESS:
    free(process_header);
    return true;
ERROR:
    free(process_header);
    return false;
}