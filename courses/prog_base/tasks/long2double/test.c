#include <check.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

#include "repr.h"

static void checkl2d(long long x) {
  if (isnan(long2double(x)) && isnan(hack_long2double(x)))
    return;
  double my_res = long2double(x);
  double right_res = hack_long2double(x);
  ck_assert(my_res == right_res);
}

START_TEST(long2double_test_fft) { checkl2d(15LL); }
END_TEST
START_TEST(long2double_test_llmin) { checkl2d(LLONG_MIN); }
END_TEST
START_TEST(long2double_test_llmax) { checkl2d(LLONG_MAX); }
END_TEST
START_TEST(long2double_test_zero) { checkl2d(0LL); }
END_TEST
START_TEST(long2double_test_val) { checkl2d(4620000000000000000LL); }
END_TEST
START_TEST(long2double_test_neg_val) { checkl2d(-4620000000000000000LL); }
END_TEST

#undef checkl2d

int main(void) {
  Suite *suite = suite_create("Long2Double");
  TCase *tcase = tcase_create("Long2Double");
  tcase_set_timeout(tcase, 60 * 10);
  tcase_add_test(tcase, long2double_test_fft);
  tcase_add_test(tcase, long2double_test_llmin);
  tcase_add_test(tcase, long2double_test_llmax);
  tcase_add_test(tcase, long2double_test_zero);
  tcase_add_test(tcase, long2double_test_val);
  tcase_add_test(tcase, long2double_test_neg_val);
  suite_add_tcase(suite, tcase);
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_VERBOSE);
  int fails = srunner_ntests_failed(sr);
  srunner_free(sr);
  return fails;
}
