#include <check.h>
#include <unistd.h>  
#include <sys/wait.h> 

#include "book.h"

START_TEST(test1)
{
    ContactList book;
    initContact(&book, 10);
    ck_assert_ptr_nonnull(book.data);
    ck_assert_int_eq(book.size, 0);
    ck_assert_int_eq(book.capacity, 10);
    freeList(&book);
}
END_TEST

START_TEST(test2)
{
    ContactList book;
    initContact(&book, 1);

    Contact c = { "X", "Y", "000", "ss" };
    addContact(&book, &c);

    deleteContact(&book, 5); // индекс вне диапазона
    ck_assert_int_eq(book.size, 1); // размер не изменился

    freeList(&book);
}
END_TEST

START_TEST(test3)
{
    ContactList book;
    initContact(&book, 1);

    Contact c = { "Doe", "John", "123456789", "@johndoe" };
    addContact(&book, &c);

    ck_assert_int_eq(book.size, 1);
    ck_assert_str_eq(book.data[0].first_name, "John");
    ck_assert_str_eq(book.data[0].last_name, "Doe");
    ck_assert_str_eq(book.data[0].phone_numbers, "123456789");
    ck_assert_str_eq(book.data[0].socials, "@johndoe");

    freeList(&book);
}
END_TEST

START_TEST(test4)
{
    ContactList book;
    initContact(&book, 1);

    Contact c = { "Smith", "Jane", "987654321", "@janesmith" };
    addContact(&book, &c);

    editContact(&book, 0, "Janet", NULL, "5555555", NULL);

    ck_assert_str_eq(book.data[0].first_name, "Janet");
    ck_assert_str_eq(book.data[0].last_name, "Smith");
    ck_assert_str_eq(book.data[0].phone_numbers, "5555555");
    ck_assert_str_eq(book.data[0].socials, "@janesmith");

    freeList(&book);
}
END_TEST

START_TEST(test5)
{
    ContactList book;
    initContact(&book, 2);

    Contact c1 = { "B", "A", "1", "s1" };
    Contact c2 = { "D", "C", "2", "s2" };
    addContact(&book, &c1);
    addContact(&book, &c2);

    deleteContact(&book, 0);

    ck_assert_int_eq(book.size, 1);
    ck_assert_str_eq(book.data[0].first_name, "C");
    ck_assert_str_eq(book.data[0].last_name, "D");
    ck_assert_str_eq(book.data[0].phone_numbers, "2");
    ck_assert_str_eq(book.data[0].socials, "s2");

    freeList(&book);
}
END_TEST

START_TEST(test6)
{
    ContactList book;
    initContact(&book, 1);

    Contact c = { "Y", "X", "000", "ss" };
    addContact(&book, &c);

    deleteContact(&book, 5); 
    ck_assert_int_eq(book.size, 1); 

    freeList(&book);
}
END_TEST

START_TEST(test7)
{
    ContactList book;
    initContact(&book, 1);

    Contact c = { "Brown", "Charlie", "111222333", "@charlieb" };
    addContact(&book, &c);

    editContact(&book, 0, "Charles", "Browne", "999888777", "@charlesb");

    ck_assert_str_eq(book.data[0].first_name, "Charles");
    ck_assert_str_eq(book.data[0].last_name, "Browne");
    ck_assert_str_eq(book.data[0].phone_numbers, "999888777");
    ck_assert_str_eq(book.data[0].socials, "@charlesb");

    freeList(&book);
}
END_TEST


Suite *phone_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Phone");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test1);
    tcase_add_test(tc_core, test2);
    tcase_add_test(tc_core, test3);
    tcase_add_test(tc_core, test4);
    tcase_add_test(tc_core, test5);
    tcase_add_test(tc_core, test6);
    tcase_add_test(tc_core, test7);

    
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = phone_suite();                     
    sr = srunner_create(s);                     

    srunner_set_fork_status(sr, CK_NOFORK);     

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
