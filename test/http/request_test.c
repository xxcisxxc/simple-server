/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include "request.h"
#include "unity.h"
#include "utils/utils.h"

struct http_message httpMessage;
struct request_line requestLine;

void setUp(void) { init_http_message(&httpMessage); }
void tearDown(void) {}

void test_parse_right_request_line0() {
    httpMessage.start_line =
        (struct start_line *)malloc_and_strcpy("GET /path/file.html HTTP/1.1");
    TEST_ASSERT(request_line_parser(&requestLine, &httpMessage));
    TEST_ASSERT_EQUAL(GET, requestLine.method);
    TEST_ASSERT_EQUAL(HTTP_1_1, requestLine.version);
    TEST_ASSERT_EQUAL_STRING("/path/file.html", requestLine.uri);

    free(requestLine.uri);
}

void test_parse_wrong_request_line0() {
    httpMessage.start_line =
        (struct start_line *)malloc_and_strcpy("post /path/file.html HTTP/1.1");
    TEST_ASSERT(!request_line_parser(&requestLine, &httpMessage));

    free(httpMessage.start_line);
}

void test_parse_wrong_request_line1() {
    httpMessage.start_line =
        (struct start_line *)malloc_and_strcpy("POST /path/file.html http/1.1");
    TEST_ASSERT(!request_line_parser(&requestLine, &httpMessage));

    free(httpMessage.start_line);
}

void test_parse_wrong_request_line2() {
    httpMessage.start_line = (struct start_line *)malloc_and_strcpy(
        "POST /path/file.html HTTP/1.1 hello");
    TEST_ASSERT(!request_line_parser(&requestLine, &httpMessage));

    free(httpMessage.start_line);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_parse_right_request_line0);
    RUN_TEST(test_parse_wrong_request_line0);
    RUN_TEST(test_parse_wrong_request_line1);
    RUN_TEST(test_parse_wrong_request_line2);
    UNITY_END();
}