/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include "response.h"
#include "unity.h"

struct response_line responseLine;

void setUp(void) {
    responseLine.status_code = 200;
    responseLine.version = HTTP_1_1;
    responseLine.reason = "OK";
}
void tearDown(void) {}

void test_construct_right_response_line() {
    char *response_line = construct_response_line(&responseLine);
    TEST_ASSERT_EQUAL_STRING("HTTP/1.1 200 OK", response_line);

    free(response_line);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_construct_right_response_line);
    UNITY_END();
}