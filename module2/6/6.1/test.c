#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "book.h" 
START_TEST(test1)
{
    ContactList list;
    initContact(&list);
    ck_assert_ptr_null(list.head);
    ck_assert_ptr_null(list.tail);

    freeList(&list);
    ck_assert_ptr_null(list.head);
    ck_assert_ptr_null(list.tail);
}
END_TEST


START_TEST(test2)
{
    ContactList list;
    initContact(&list);

    Contact c1 = {.first_name="Ivan", .last_name="Petrov", .phone_numbers="", .socials=""};
    Contact c2 = {.first_name="Anna", .last_name="Ivanova", .phone_numbers="", .socials=""};
    Contact c3 = {.first_name="Sergey", .last_name="Sidorov", .phone_numbers="", .socials=""};

    addContact(&list, &c1);
    addContact(&list, &c2);
    addContact(&list, &c3);

    ck_assert_str_eq(list.head->data.last_name, "Ivanova");
    ck_assert_str_eq(list.head->next->data.last_name, "Petrov");
    ck_assert_str_eq(list.tail->data.last_name, "Sidorov");

    freeList(&list);
}
END_TEST


START_TEST(test3)
{
    ContactList list;
    initContact(&list);

    Contact c = {.first_name="Ivan", .last_name="Petrov", .phone_numbers="123", .socials="vk"};
    addContact(&list, &c);

    editContact(&list, 0, "Pavel", "Antonov", "456", "telegram");

    ck_assert_str_eq(list.head->data.first_name, "Pavel");
    ck_assert_str_eq(list.head->data.last_name, "Antonov");
    ck_assert_str_eq(list.head->data.phone_numbers, "456");
    ck_assert_str_eq(list.head->data.socials, "telegram");

    freeList(&list);
}
END_TEST


START_TEST(test4)
{
    ContactList list;
    initContact(&list);

    Contact c1 = {.first_name="Ivan", .last_name="Petrov", .phone_numbers="", .socials=""};
    Contact c2 = {.first_name="Anna", .last_name="Ivanova", .phone_numbers="", .socials=""};
    addContact(&list, &c1);
    addContact(&list, &c2);

    deleteContact(&list, 0);

    ck_assert_str_eq(list.head->data.last_name, "Petrov");
    ck_assert_ptr_null(list.head->prev);
    ck_assert_ptr_null(list.tail->next);

    freeList(&list);
}
END_TEST


Suite* contact_suite(void)
{
    Suite *s = suite_create("ContactList");

    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test1);
    tcase_add_test(tc_core, test2);
    tcase_add_test(tc_core, test3);
    tcase_add_test(tc_core, test4);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int failed;
    Suite *s = contact_suite();
    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
