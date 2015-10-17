#include <check.h>
#include <stdio.h>
#include <limits.h>
#include "repr.h"

START_TEST (long2double_test){
  char buf1[1000];
  char buf2[1000];

  for(long long i = LONG_MIN;i<LONG_MAX-50001;i+=50000){
    double a = hack_long2double(i);
    double b = long2double(i);
    sprintf(buf1,"%f",a);
    sprintf(buf2,"%f",b);
    ck_assert_str_eq(buf1,buf2);
  }
} END_TEST

int main(void){
  Suite* suite = suite_create("Long2Double");
  TCase* tcase  = tcase_create("Long2Double");
  tcase_add_test(tcase,long2double_test);
  suite_add_tcase(suite,tcase);
  SRunner* sr = srunner_create(suite);
  srunner_run_all(sr,CK_VERBOSE);
  int fails = srunner_ntests_failed(sr);
  srunner_free(sr);
  return fails;
}
