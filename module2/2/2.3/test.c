#include <check.h>
#include <unistd.h>  
#include <sys/wait.h> 

#include "calculator2.h"

START_TEST(test1)
{
    double numbers[] = {1.0, 2.0, 3.0, 4.0};
    
    ck_assert_double_eq(sum(2, numbers[0], numbers[1]), 3.0);
    ck_assert_double_eq(sum(3, numbers[0], numbers[1], numbers[2]), 6.0);
    ck_assert_double_eq(sum(4, numbers[0], numbers[1], numbers[2], numbers[3]), 10.0);
}
END_TEST

START_TEST(test2)
{
    double numbers[] = {40.0, 3.0, 2.0, 1.0};
    
    ck_assert_double_eq(sub(2, numbers[0], numbers[1]), 37.0);
    ck_assert_double_eq(sub(3, numbers[0], numbers[1], numbers[2]), 35.0);
    ck_assert_double_eq(sub(4, numbers[0], numbers[1], numbers[2], numbers[3]), 34.0);
}
END_TEST

START_TEST(test3)
{
    double numbers[] = {40.0, 3.0, 2.0, 0.0};
    
    ck_assert_double_eq(mul(2, numbers[0], numbers[1]), 120.0);
    ck_assert_double_eq(mul(3, numbers[0], numbers[1], numbers[2]), 240.0);
    ck_assert_double_eq(mul(4, numbers[0], numbers[1], numbers[2], numbers[3]), 0.0);
}
END_TEST

START_TEST(test4)
{
    double numbers[] = {40.0, 3.0, 2.0, 6.0};
    
    ck_assert_double_eq_tol(divide(2, numbers[0], numbers[1]), 13.33, 0.01);
    ck_assert_double_eq_tol(divide(3, numbers[0], numbers[1], numbers[2]), 6.67, 0.01);
    ck_assert_double_eq_tol(divide(4, numbers[0], numbers[1], numbers[2], numbers[3]), 1.11, 0.01);

}
END_TEST

START_TEST(test5)
{
    ck_assert_double_eq(sum(1, 5.0), 5.0);
    ck_assert_double_eq(sub(1, 5.0), 5.0);
    ck_assert_double_eq(mul(1, 5.0), 5.0);
    ck_assert_double_eq(divide(1, 5.0), 5.0);
}
END_TEST

START_TEST(test6)
{
    ck_assert_double_eq(sum(3, 0.0, 0.0, 0.0), 0.0);
    ck_assert_double_eq(sub(3, 0.0, 0.0, 0.0), 0.0);
    ck_assert_double_eq(mul(3, 0.0, 0.0, 0.0), 0.0);
}
END_TEST

START_TEST(test7)
{
    if (fork() == 0) {
        double res = divide(2, 5.0, 0.0);
        (void)res; 
        exit(1); 
    } else {
        int status;
        wait(&status);
        ck_assert_msg(WIFEXITED(status) && WEXITSTATUS(status) == 1, "Expected exit on division by zero");
    }
}
END_TEST

Suite *calculator_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Calculator");

    /* Core test case */
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

    s = calculator_suite();                     
    sr = srunner_create(s);                     

    srunner_set_fork_status(sr, CK_NOFORK);     

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
