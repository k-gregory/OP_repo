#pragma once

#include "univsec_wicket.h"

#include <check.h>
#include <stdlib.h>
#include <stdio.h> //sprintf

START_TEST(univsec_wicket_pass_saves_passers) {
#define td_length 30
  char name_buff[256];
  univ_person* passers[td_length];
  univ_person* wicket_reply[td_length];
  size_t wicket_reply_length;

  univsec_wicket* w = univsec_wicket_new();

  for(size_t i = 0; i < td_length; i++){
    sprintf(name_buff,"%zu",i);
    passers[i] = univ_person_new(name_buff, UNIV_PERSON_STUDENT);
  }
  
  for(size_t i = 0; i < td_length; i++){
    univsec_wicket_pass(w,passers[i]);
  }
  wicket_reply_length = univsec_wicket_get_passes(w,
						  wicket_reply,
						  td_length);
  ck_assert_uint_eq(wicket_reply_length, td_length);
  for(size_t  i= 0; i< td_length; i++)
    ck_assert_ptr_eq(wicket_reply[i],passers[td_length - i -1]);
  

  for(size_t i = 0; i < td_length; i++){
    univ_person_free(passers[i]);
  }
  univsec_wicket_free(w);
#undef td_length
} END_TEST

START_TEST(univsec_wicket_get_passes_result_NULL_error_returns_0){
  size_t ret;
  univsec_wicket* w = univsec_wicket_new();

  univ_person** res = NULL;
  ret = univsec_wicket_get_passes(w, res, 10);
  ck_assert_uint_eq(ret, 0);
  ck_assert(univsec_wicket_get_error() == UNIVSEC_WICKET_S_BADPOLLOUT);
  
  univsec_wicket_free(w);
} END_TEST

START_TEST(univsec_wicket_get_passes_zero_length_buffer_ret_0){
  size_t wicket_reply_length;
  univsec_wicket* w = univsec_wicket_new();
  univ_person* res[1];

  wicket_reply_length = univsec_wicket_get_passes(w,
						  res,
						  0);
  ck_assert_uint_eq(wicket_reply_length, 0);
  
  univsec_wicket_free(w);
} END_TEST

START_TEST(univsec_wicket_get_passes_small_buffer){
#define td_length 30
  char name_buff[256];
  univ_person* passers[td_length];
  univ_person* reply_buff[1];
  size_t wicket_reply_length;

  univsec_wicket* w = univsec_wicket_new();

  for(size_t i = 0; i < td_length; i++){
    sprintf(name_buff,"%zu",i);
    passers[i] = univ_person_new(name_buff, UNIV_PERSON_STUDENT);
    univsec_wicket_pass(w, passers[i]);
  }


  for(size_t i = 0; i < td_length; i++){
    wicket_reply_length = univsec_wicket_get_passes(w, reply_buff,1);
    ck_assert_uint_eq(wicket_reply_length, 1);
    ck_assert_ptr_eq(reply_buff[0], passers[td_length - i -1]);
  }
  

  for(size_t i = 0; i < td_length; i++){
    univ_person_free(passers[i]);
  }
  univsec_wicket_free(w);
#undef td_length  
} END_TEST

Suite* univsec_wicket_suite(){
  Suite* ret;
  TCase* tc_core;

  ret = suite_create("univsec_wicket");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core,
		 univsec_wicket_pass_saves_passers);
  tcase_add_test(tc_core,
		 univsec_wicket_get_passes_result_NULL_error_returns_0);
  tcase_add_test(tc_core,
		 univsec_wicket_get_passes_zero_length_buffer_ret_0);
  tcase_add_test(tc_core,
		 univsec_wicket_get_passes_small_buffer);

  suite_add_tcase(ret,tc_core);  
  return ret;
}
