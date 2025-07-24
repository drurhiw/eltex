#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"  

START_TEST(test1) {
    ContactTree book;
    initContact(&book);

    Contact c = {
        .first_name = "Ivan",
        .last_name = "Ivanov",
        .phone_numbers = "1234567890",
        .socials = "vk.com/ivan"
    };

    addContact(&book, &c);

    ContactNode *node = findNode(book.root, "Ivanov");
    ck_assert_ptr_nonnull(node);
    ck_assert_str_eq(node->data->first_name, "Ivan");
    ck_assert_str_eq(node->data->phone_numbers, "1234567890");
    ck_assert_str_eq(node->data->socials, "vk.com/ivan");

    freeNode(book.root);
}
END_TEST

START_TEST(test2) {
    ContactTree book;
    initContact(&book);

    Contact c1 = {.first_name = "Ivan", .last_name = "Ivanov"};
    Contact c2 = {.first_name = "Petr", .last_name = "Petrov"};

    addContact(&book, &c1);
    addContact(&book, &c2);

    book.root = deleteContact(book.root, "Ivanov");
    ContactNode *node = findNode(book.root, "Ivanov");
    ck_assert_ptr_null(node);

    node = findNode(book.root, "Petrov");
    ck_assert_ptr_nonnull(node);

    freeNode(book.root);
}
END_TEST

START_TEST(test3) {
    ContactTree book;
    initContact(&book);

    Contact c = {.first_name = "Ivan", .last_name = "Ivanov"};
    addContact(&book, &c);

    Contact updated = {.first_name = "IvanUpdated", .last_name = "Ivanov", .phone_numbers = "11111", .socials = "new_social"};
    editContact(&book, "Ivanov", &updated);

    ContactNode *node = findNode(book.root, "Ivanov");
    ck_assert_ptr_nonnull(node);
    ck_assert_str_eq(node->data->first_name, "IvanUpdated");
    ck_assert_str_eq(node->data->phone_numbers, "11111");
    ck_assert_str_eq(node->data->socials, "new_social");

    freeNode(book.root);
}
END_TEST

Suite *contacts_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Contacts");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test1);
    tcase_add_test(tc_core, test2);
    tcase_add_test(tc_core, test3);

    suite_add_tcase(s, tc_core);

    return s;
}


int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = contacts_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
