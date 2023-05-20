/*
 * Copyright (c) 2023. Created by xxcisxxc
 */

#include "message.h"
#include "unity.h"

struct http_message httpMessage;

void setUp(void) { init_http_message(&httpMessage); }
void tearDown(void) {}

void test_parse_right_http_message0() {
    char raw_message[] = "GET /path/file.html HTTP/1.1\n"
                         "From: hello@example.com\n"
                         "User-Agent: HTTPTool/1.0\n"
                         "\n"
                         "Hello World";
    TEST_ASSERT(http_message_parser(&httpMessage, raw_message));
    TEST_ASSERT_EQUAL_STRING("GET /path/file.html HTTP/1.1",
                             (char *)httpMessage.start_line);
    TEST_ASSERT_EQUAL_STRING("Hello World", httpMessage.message_body.body);

    struct header_field *current_header =
        (struct header_field *)
            httpMessage.header_field_list.list_head.next->data;
    TEST_ASSERT_EQUAL_STRING("From", current_header->field_name);
    TEST_ASSERT_EQUAL_STRING("hello@example.com", current_header->field_value);

    current_header =
        (struct header_field *)current_header->list_head.next->data;
    TEST_ASSERT_EQUAL_STRING("User-Agent", current_header->field_name);
    TEST_ASSERT_EQUAL_STRING("HTTPTool/1.0", current_header->field_value);

    free(httpMessage.start_line);
    free(httpMessage.message_body.body);
    free_list(&httpMessage.header_field_list.list_head, true);
}

void test_parse_wrong_http_message0() {
    char raw_message[] = "GET /path/file.html HTTP/1.1\n"
                         "From: hello@example.com\n"
                         "User-Agent: HTTPTool/1.0\n"
                         "Hello World";
    TEST_ASSERT(!http_message_parser(&httpMessage, raw_message));
}

void test_parse_wrong_http_message1() {
    char raw_message[] = "GET /path/file.html HTTP/1.1\n"
                         "From: hello@example.com\n"
                         "User-Agent: HTTPTool/1.0\n";
    TEST_ASSERT(!http_message_parser(&httpMessage, raw_message));
}

void test_parse_right_http_message1() {
    char raw_message[] = "GET /path/file.html HTTP/1.1\n"
                         "From: hello@example.com\n"
                         "User-Agent: HTTPTool/1.0\n"
                         "\n";
    TEST_ASSERT(http_message_parser(&httpMessage, raw_message));
    TEST_ASSERT_EQUAL_STRING("", httpMessage.message_body.body);

    free(httpMessage.start_line);
    free(httpMessage.message_body.body);
    free_list(&httpMessage.header_field_list.list_head, true);
}

void test_parse_right_http_message2() {
    char raw_message[] = "GET /path/file.html HTTP/1.1\n"
                         "\n";
    TEST_ASSERT(http_message_parser(&httpMessage, raw_message));
    TEST_ASSERT_EQUAL_STRING("", httpMessage.message_body.body);

    free(httpMessage.start_line);
    free(httpMessage.message_body.body);
    free_list(&httpMessage.header_field_list.list_head, true);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_parse_right_http_message0);
    RUN_TEST(test_parse_wrong_http_message0);
    RUN_TEST(test_parse_wrong_http_message1);
    RUN_TEST(test_parse_right_http_message1);
    RUN_TEST(test_parse_right_http_message2);
    UNITY_END();
}