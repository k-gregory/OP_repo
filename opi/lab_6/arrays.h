#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include <stdlib.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef int (*fold_f)(int, int);

int foldr(int accum, int *arr_first, int *arr_last, fold_f f);
int f_max(int a, int b);
int f_min(int a, int b);
int f_sum(int acc, int next);
size_t find_first(int value, int arr[], size_t len);
size_t find(int arr[], size_t len);
void print_array(int arr[], size_t len);
void initialize_array(int arr[], size_t len);
int copy(int arr1[], int arr2[], size_t arr1_len, size_t arr2_len);
double sum_average(int arr[], size_t arr_len);

#endif
