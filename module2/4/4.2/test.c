#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

START_TEST(test1)
{
    PriorityQueue q = {NULL, NULL};
    add(&q, 5, "A");
    add(&q, 2, "B");
    add(&q, 7, "C");

    char *result = dequeue(&q);
    ck_assert_str_eq(result, "B");
    free(result);

    result = dequeue(&q);
    ck_assert_str_eq(result, "A");
    free(result);

    result = dequeue(&q);
    ck_assert_str_eq(result, "C");
    free(result);

    ck_assert_ptr_null(q.head);
    ck_assert_ptr_null(q.tail);
}
END_TEST

START_TEST(test2)
{
    PriorityQueue q = {NULL, NULL};
    add(&q, 5, "First");
    add(&q, 5, "Second");
    add(&q, 5, "Third");

    char *result = dequeue(&q);
    ck_assert_str_eq(result, "First");
    free(result);

    result = dequeue(&q);
    ck_assert_str_eq(result, "Second");
    free(result);

    result = dequeue(&q);
    ck_assert_str_eq(result, "Third");
    free(result);

    ck_assert_ptr_null(q.head);
    ck_assert_ptr_null(q.tail);
}
END_TEST


START_TEST(test3)
{
    PriorityQueue q = {NULL, NULL};
    add(&q, 2, "one");
    add(&q, 6, "two");
    add(&q, 10, "three");

    char *result = dequeueMinPriority(&q, 5);
    ck_assert_str_eq(result, "two");
    free(result);

    result = dequeueMinPriority(&q, 7);
    ck_assert_str_eq(result, "three");
    free(result);

    result = dequeueMinPriority(&q, 11);
    ck_assert_ptr_null(result);
}
END_TEST

Suite* queue_suite(void)
{
    Suite *s = suite_create("PriorityQueue");

    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test1);
    tcase_add_test(tc_core, test2);
    tcase_add_test(tc_core, test3);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = queue_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
