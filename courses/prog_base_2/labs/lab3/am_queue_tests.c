#pragma once

#include "am_queue.h"

#include <check.h>
#include <stdlib.h>

START_TEST(am_queue_add_saves_items){
  am_queue* q;
  int i;  
  q = am_queue_new();

  for(i = 0; i <= 30; i++)
    am_queue_add(q, i);
  for(i = 0; i <= 30; i++){
    int res;
    ck_assert(am_queue_peek(q,&res) == AM_QUEUE_OK);
    ck_assert_int_eq(res, i);
    am_queue_remove(q);
  }
  
  am_queue_free(q);
} END_TEST

START_TEST(am_queue_add_more_than_delete_saves_items){
  am_queue* q;
  int i,n;
  q = am_queue_new();

  for(i = 0; i < 20;){
    am_queue_add(q, i);
    am_queue_add(q, i+1);
    am_queue_remove(q);
    i+=2;
  }
  
  for(i = 0,n=am_queue_contains(q); i < n;i++){
    int res;
    ck_assert(am_queue_peek(q, &res) == AM_QUEUE_OK);
    ck_assert_int_eq(i+10, res);
    am_queue_remove(q);
  }
    
  am_queue_free(q);
} END_TEST

START_TEST(am_queue_peek_empty_returns_error){
  am_queue* q;
  int unused;

  q = am_queue_new();

  ck_assert(am_queue_peek(q,&unused) == AM_QUEUE_EMPTY);

  am_queue_free(q);
} END_TEST

START_TEST(am_queue_remove_empty_returns_error){
  am_queue* q;

  q = am_queue_new();

  ck_assert(am_queue_remove(q) == AM_QUEUE_EMPTY);

  am_queue_free(q);
} END_TEST

START_TEST(am_queue_contains_empty_returns_0){
  am_queue* q;
  q = am_queue_new();
  
  ck_assert(am_queue_contains(q) == 0);
  
  am_queue_free(q);
} END_TEST

START_TEST(am_queue_add_changes_contains_result){
  am_queue* q;
  q = am_queue_new();

  am_queue_add(q, 0);
  ck_assert(am_queue_contains(q) == 1);
  
  am_queue_add(q, 0);
  ck_assert(am_queue_contains(q) == 2);
  
  am_queue_add(q, 0);
  ck_assert(am_queue_contains(q) == 3);
  
  am_queue_add(q, 0);
  ck_assert(am_queue_contains(q) == 4);
  
  am_queue_free(q);
} END_TEST

Suite* am_queue_suite(){
  Suite* ret;
  TCase* tc_core;

  ret = suite_create("am_queue");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, am_queue_add_more_than_delete_saves_items);
  tcase_add_test(tc_core, am_queue_add_saves_items);
  tcase_add_test(tc_core, am_queue_contains_empty_returns_0);
  tcase_add_test(tc_core, am_queue_add_changes_contains_result);
  tcase_add_test(tc_core, am_queue_peek_empty_returns_error);
  tcase_add_test(tc_core, am_queue_remove_empty_returns_error);  

  suite_add_tcase(ret, tc_core);
  return ret;
}

