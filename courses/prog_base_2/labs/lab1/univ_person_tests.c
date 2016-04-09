#pragma once

#include "univ_person.h"

#include <check.h>
#include <stdlib.h>

START_TEST(univ_person_new_NULL_name_error) {
  univ_person *ret = univ_person_new(NULL, UNIV_PERSON_STUDENT);
  ck_assert_ptr_eq(ret, NULL);
  ck_assert(univ_person_get_error() == UNIV_PERSON_S_BADNAME);
}
END_TEST

START_TEST(univ_person_new_name_is_saved) {
  univ_person *p = univ_person_new("Name", UNIV_PERSON_SERVICE_STUFF);

  char *person_name = univ_person_get_name(p, NULL, 0);

  ck_assert_str_eq("Name", person_name);

  univ_person_free(p);
  free(person_name);
}
END_TEST

START_TEST(univ_person_new_category_is_saved) {
  univ_person *p = univ_person_new("Name", UNIV_PERSON_STUDENT);

  ck_assert(univ_person_get_category(p) == UNIV_PERSON_STUDENT);

  univ_person_free(p);
}
END_TEST

START_TEST(univ_person_get_name_respects_non_null_dest) {
  char person_name[20];
  univ_person *p = univ_person_new("Name", UNIV_PERSON_SERVICE_STUFF);

  char *res = univ_person_get_name(p, person_name, 20);
  ck_assert_ptr_eq(res, person_name);
  ck_assert_str_eq("Name", person_name);
  univ_person_free(p);
}
END_TEST

START_TEST(univ_person_get_name_respects_null_dest){
  univ_person *p = univ_person_new("John", UNIV_PERSON_STUDENT);
  char *res = univ_person_get_name(p, NULL, 0);

  ck_assert_str_eq("John", res);
  
  free(res);
  univ_person_free(p);
}
END_TEST

Suite *univ_person_suite() {
  Suite *ret;
  TCase *tc_core;

  ret = suite_create("univ_person");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, univ_person_new_name_is_saved);
  tcase_add_test(tc_core, univ_person_new_category_is_saved);
  tcase_add_test(tc_core, univ_person_get_name_respects_non_null_dest);
  tcase_add_test(tc_core, univ_person_get_name_respects_null_dest);
  tcase_add_test(tc_core, univ_person_new_NULL_name_error);

  suite_add_tcase(ret, tc_core);
  return ret;
}
