//
// Copyright xxcisxxc.
//

#ifndef SIMPLE_SERVER_REQUEST_H
#define SIMPLE_SERVER_REQUEST_H

struct request_line {
    unsigned int len_url;
    char *url;

    unsigned int len_method;
    char *method; // HTTP Method

    unsigned int len_rpath;
    char *rpath; // Relative Path

    unsigned int len_version;
    char *version; // Version of HTTP
};
typedef struct request_line request_line_t;

struct header {};

#endif // SIMPLE_SERVER_REQUEST_H
