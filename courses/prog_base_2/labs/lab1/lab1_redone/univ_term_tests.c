#pragma once

#include "univ_term.h"

#include <check.h>
#include <stdlib.h>

START_TEST(univ_term_new_too_many_output_error) {
  univ_term *ret = univ_term_new(UNIV_TERM_MAX_OUTPUT_NUMBER + 1,
                                   42,
				   UNIV_PERSON_STUDENT);
  ck_assert_ptr_eq(ret, NULL);
  ck_assert(univ_term_get_error() == UNIV_TERM_S_TOOMANY_OUTPUT);
}
END_TEST

Suite *univ_term_suite() {
  Suite *ret;
  TCase *tc_core;

  ret = suite_create("univ_term");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, univ_term_new_too_many_output_error);


  suite_add_tcase(ret, tc_core);
  return ret;
}
