/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#ifndef SIMPLE_SERVER_UTILS_H
#define SIMPLE_SERVER_UTILS_H

#include <stdio.h>

#define ERROR_MESSAGE(...) fprintf(stderr, __VA_ARGS__)

static inline char *malloc_and_strcpy(const char *restrict src) {
    char *dst = malloc(strlen(src));
    return strcpy(dst, src);
}

#endif // SIMPLE_SERVER_UTILS_H
