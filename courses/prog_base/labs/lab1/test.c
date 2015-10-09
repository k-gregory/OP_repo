#include <check.h>

#include "math.c"
#include "condition.c"
#include "switch.c"

/*MATH TESTS{{{*/
START_TEST(test_math_results) {
  ck_assert(calc(5, 4, 3) >= 0);
  ck_assert(calc(3, 3, 3) == INFINITY);
  ck_assert(calc(132, 84, 3) == 4.8794447709045984e+179);
  ck_assert(calc(1, -0.99, 0.1) < 0);
  ck_assert(calc(1, -0.999, 0.1) > calc(1, -0.99999, 0.1));
}
END_TEST
/*MATH TESTS}}}*/

/*CONDITIONS TESTS{{{*/
START_TEST(test_condition_case_1) {
  ck_assert_int_eq(satisfies(-128, -128, -128), 0);
  ck_assert_int_eq(satisfies(-10, -20, -21), 1);
  ck_assert_int_eq(satisfies(-1, -2, -3), 0);
}
END_TEST

START_TEST(test_condition_case_2) {
  ck_assert_int_eq(satisfies(1, -2, 3), 1);
  ck_assert_int_eq(satisfies(15, -256, 10), 0);
  ck_assert_int_eq(satisfies(11, -12, -3), 1);
  ck_assert_int_eq(satisfies(-4, 5, -6), 1);
}
END_TEST

START_TEST(test_condition_case_3) {
  ck_assert_int_eq(satisfies(1, 2, 3), 0);
  ck_assert_int_eq(satisfies(100, 200, 300), 1);
  ck_assert_int_eq(satisfies(1, 2, 33), 0);
  ck_assert_int_eq(satisfies(1, 2, 34), 1);
}
END_TEST
/*CONDITIONS TESTS}}}*/

/*SWITCH TESTS{{{*/
START_TEST(test_switch_basic_ops) {
  ck_assert_int_eq(exec(6, 2, 5), 32);
  ck_assert_int_eq(exec(-6, 2, 5), 25);

  ck_assert_int_eq(exec(2, 2, -5), 7);
  ck_assert_int_eq(exec(-2, 2, -5), -7);

  ck_assert_int_eq(exec(7, 25, 40), exec(13, 25, 40));
  ck_assert_int_eq(exec(13, 25, 4), exec(77, 21, 4));

  ck_assert_int_eq(exec(11, 3, 2), 2);
  ck_assert_int_eq(exec(11, 1, 2), 6);
  ck_assert_int_eq(exec(11, 3, 3), -2);
}
END_TEST

START_TEST(test_switch_type_sizes) {
  ck_assert_int_eq(exec(10, -2, -22), sizeof(float) * 2);
  ck_assert_int_eq(exec(10, -100, -1), sizeof(signed char) * 100);
  ck_assert_int_eq(exec(10, 0, 0), 0);
}
END_TEST

START_TEST(test_switch_unusual_args) {
  ck_assert_int_eq(exec(100, 1, 2), -1);
  ck_assert_int_eq(exec(98, 1, 2), 2);
}
END_TEST
/*SWITCH TESTS}}}*/

Suite *lab_suite() {
  Suite *s = suite_create("Lab");
  TCase *tc_math, *tc_condition, *tc_switch;

  tc_math = tcase_create("Math");
  tcase_add_test(tc_math, test_math_results);

  tc_condition = tcase_create("Condition");
  tcase_add_test(tc_condition, test_condition_case_1);
  tcase_add_test(tc_condition, test_condition_case_2);
  tcase_add_test(tc_condition, test_condition_case_3);

  tc_switch = tcase_create("Switch");
  tcase_add_test(tc_switch, test_switch_basic_ops);
  tcase_add_test(tc_switch, test_switch_unusual_args);
  tcase_add_test(tc_switch, test_switch_type_sizes);

  suite_add_tcase(s, tc_math);
  suite_add_tcase(s, tc_condition);
  suite_add_tcase(s, tc_switch);

  return s;
}

int main() {
  Suite *s = lab_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);

  int num_tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return num_tests_failed;
}
