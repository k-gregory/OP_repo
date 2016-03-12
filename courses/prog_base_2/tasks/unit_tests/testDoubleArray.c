#include "DoubleArray.h"
#include <check.h>
#include <assert.h>
#include <math.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

START_TEST(double_array_new_zero_size_ret_null){
  DoubleArray* arr = DoubleArray_new(0);
  ck_assert_ptr_eq(arr,NULL);
} END_TEST

START_TEST(double_array_new_with_zeroes_zero_size_ret_null){
  DoubleArray* arr = DoubleArray_new_with_zeroes(0);
  ck_assert_ptr_eq(arr,NULL);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_new_with_zeroes_contains_only_zeroes){
  const size_t size = 20;
  DoubleArray* arr = DoubleArray_new_with_zeroes(size);
  for(size_t i = 0; i < size; i++)
    ck_assert(*DoubleArray_at(arr,i) == 0);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_at_random_access_saves_data_correctly) {
  double values[] = {1.32,53,0,32.82,2.3,15.65,121.1,554.32};
  int  indicies[] = {5   , 2,7,    6,  4,    0,    1,     3};
  assert(LEN(values) == LEN(indicies));

  DoubleArray* arr = DoubleArray_new(8);
  for(size_t i = 0; i < 8; i++)
    *DoubleArray_at(arr,indicies[i]) = values[i];
  for(size_t i = 0; i < 8; i++)
    ck_assert(*DoubleArray_at(arr,indicies[i]) == values[i]);
  DoubleArray_delete(arr);
  
} END_TEST

START_TEST(double_array_at_out_of_bounds_index_ret_null){
  DoubleArray* arr = DoubleArray_new(10);
  ck_assert_ptr_eq(NULL, DoubleArray_at(arr, 42));
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_size_not_changed){
  const size_t size = 15;
  DoubleArray* arr = DoubleArray_new(size);
  ck_assert_uint_eq(size, DoubleArray_size(arr));
  *DoubleArray_at(arr,1) = 42;
  ck_assert_uint_eq(size, DoubleArray_size(arr));
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_min_ret_min) {
  double t_v[] = {1, -4.4, -4.39, 64,500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_min(arr) == -4.4);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_max_ret_max) {
  double t_v[] = {-50, -4.4, -4.39, -64,-500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_max(arr) == -4.39);
  DoubleArray_delete(arr);  
} END_TEST

int double_abs_compare(double a, double b){
  double res = fabs(a) - fabs(b);
  if(res < 0) return -1;
  if(res > 0) return 1;
  return 0;
}

START_TEST(double_array_max_by_predicate_abs_comare){
  double t_v[] = {-50, -4.4, -4.39, -64,-500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_max_by(arr,double_abs_compare) == -500);
  DoubleArray_delete(arr);  
} END_TEST

START_TEST(double_array_contains_first_ret_1){
  double t_v[] = {-50, -4.4, -4.39, -64,-500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_contains(arr,-50) == 1);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_contains_last_ret_1){
  double t_v[] = {-50, -4.4, -4.39, -64,-500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_contains(arr, -500) == 1);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_contains_nonelement_ret_0) {
  double t_v[] = {-50, -4.4, -4.39, -64,-500};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_contains(arr,42) == 0);
  DoubleArray_delete(arr);
} END_TEST

START_TEST(double_array_min_max_max_by_constains_length_restriction_is_respected){
  double t_v[] = {-50, -4.4, -4.39, -64,-700,600,-700,42};
  DoubleArray* arr = DoubleArray_new(LEN(t_v));
  for(size_t i = 0; i < LEN(t_v); i++)
    *DoubleArray_at(arr,i) = t_v[i];
  ck_assert(DoubleArray_min_l(arr,6) == -700);
  ck_assert(DoubleArray_max_l(arr,2) == -4.4);
  ck_assert(DoubleArray_max_by_l(arr,double_abs_compare,6) == -700);
  ck_assert(DoubleArray_contains_l(arr,42,6) == 0);
  ck_assert(DoubleArray_contains_l(arr,-50,1) == 1);
  DoubleArray_delete(arr);  
} END_TEST

Suite* double_array_suite(){
  Suite* ret;
  TCase* tc_core;

  ret = suite_create("double_array");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core,
		 double_array_new_zero_size_ret_null);
  tcase_add_test(tc_core,
		 double_array_new_with_zeroes_zero_size_ret_null);
  tcase_add_test(tc_core,
		 double_array_new_with_zeroes_contains_only_zeroes);
  tcase_add_test(tc_core,
		 double_array_at_random_access_saves_data_correctly);
#ifndef DOUBLE_ARRAY_NO_INDEX_CHECK
  tcase_add_test(tc_core,
		 double_array_at_out_of_bounds_index_ret_null);
#endif
  tcase_add_test(tc_core,
		 double_array_size_not_changed);
  tcase_add_test(tc_core,
		 double_array_min_ret_min);
  tcase_add_test(tc_core,
		 double_array_max_ret_max);
  tcase_add_test(tc_core,
 		 double_array_max_by_predicate_abs_comare);
  tcase_add_test(tc_core,
		 double_array_contains_first_ret_1);
  tcase_add_test(tc_core,
		 double_array_contains_last_ret_1);
  tcase_add_test(tc_core,
		 double_array_contains_nonelement_ret_0);
  tcase_add_test(tc_core,
  double_array_min_max_max_by_constains_length_restriction_is_respected);

  suite_add_tcase(ret, tc_core);

  return ret;
}


int main(void){
  Suite* s;
  SRunner* sr;
  int num_failed;
  s = double_array_suite();
  sr = srunner_create(s);
  srunner_run_all(sr,CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
