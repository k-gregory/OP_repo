#include <check.h>
#include <stdio.h>
#include <limits.h>
#include "repr.h"

#define STEP 5000000

START_TEST(long2double_test) {
  for (long long x = -LLONG_MIN; x < LLONG_MAX; x += STEP) {
    ck_assert(long2double(x) == hack_long2double(x));
  }
}
END_TEST

int main(void) {
  Suite *suite = suite_create("Long2Double");
  TCase *tcase = tcase_create("Long2Double");
  tcase_set_timeout(tcase, 60 * 10);
  tcase_add_test(tcase, long2double_test);
  suite_add_tcase(suite, tcase);
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_VERBOSE);
  int fails = srunner_ntests_failed(sr);
  srunner_free(sr);
  return fails;
}
