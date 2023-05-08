#include "list.h"
#include "unity.h"

struct test_list {
    int test;
    struct list list_head;
};
typedef struct test_list test_list_t;
test_list_t test_list;

void setUp(void) {
    test_list.test = 0;
    init_list_head(&test_list.list_head);
}
void tearDown(void) {}

void test_initialize_list_head() {
    TEST_ASSERT_EQUAL(0, test_list.test);
    TEST_ASSERT_EQUAL(test_list.list_head.prev, test_list.list_head.next);
    TEST_ASSERT_EQUAL(NULL, test_list.list_head.data);
}

void test_initialize_list_item() {
    test_list_t new_item = {.test = 1};
    init_list_item(&new_item.list_head, &new_item);
    TEST_ASSERT_EQUAL(1, new_item.test);
    TEST_ASSERT_EQUAL(new_item.list_head.prev, new_item.list_head.next);
    TEST_ASSERT_EQUAL(&new_item, new_item.list_head.data);
}

void test_add_delete_list_item() {
    test_list_t new_item0 = {.test = 1};
    init_list_item(&new_item0.list_head, &new_item0);

    add_list_item_front(&test_list.list_head, &new_item0.list_head);
    TEST_ASSERT_EQUAL(&new_item0, test_list.list_head.next->data);
    TEST_ASSERT_EQUAL(&new_item0, test_list.list_head.prev->data);
    TEST_ASSERT_EQUAL(&test_list.list_head, new_item0.list_head.prev);
    TEST_ASSERT_EQUAL(NULL, new_item0.list_head.next->data);

    test_list_t new_item1 = {.test = 2};
    init_list_item(&new_item1.list_head, &new_item1);

    add_list_item_end(&test_list.list_head, &new_item1.list_head);
    TEST_ASSERT_EQUAL(&new_item1, test_list.list_head.prev->data);
    TEST_ASSERT_EQUAL(&new_item0, test_list.list_head.next->data);
    TEST_ASSERT_EQUAL(NULL, new_item0.list_head.prev->data);
    TEST_ASSERT_EQUAL(&new_item1, new_item0.list_head.next->data);
    TEST_ASSERT_EQUAL(&new_item0, new_item1.list_head.prev->data);
    TEST_ASSERT_EQUAL(&test_list.list_head, new_item1.list_head.next);

    test_list_t new_item2 = {.test = 3};
    init_list_item(&new_item2.list_head, &new_item2);
    add_list_item_front(&test_list.list_head, &new_item2.list_head);

    free_list_item(&new_item1.list_head, false);
    TEST_ASSERT_EQUAL(&new_item0, test_list.list_head.prev->data);
    TEST_ASSERT_EQUAL(&new_item2, test_list.list_head.next->data);
    TEST_ASSERT_EQUAL(&new_item2, new_item0.list_head.prev->data);
    TEST_ASSERT_EQUAL(NULL, new_item0.list_head.next->data);
    TEST_ASSERT_EQUAL(&test_list.list_head, new_item2.list_head.prev);
    TEST_ASSERT_EQUAL(&new_item0, new_item2.list_head.next->data);

    add_list_item_front(&test_list.list_head, &new_item1.list_head);

    free_list(&test_list.list_head, false);
    TEST_ASSERT_EQUAL(&test_list.list_head, test_list.list_head.next);
    TEST_ASSERT_EQUAL(test_list.list_head.prev, test_list.list_head.next);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initialize_list_head);
    RUN_TEST(test_initialize_list_item);
    RUN_TEST(test_add_delete_list_item);
    UNITY_END();
}