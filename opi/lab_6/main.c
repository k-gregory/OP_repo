// Grigorij Komar, task number 5.
// Find() searches for element which is between
// biggest and smallest elements
// Copy copies from arr1 to arr2 elements [1;find(arr1)]
#include <stdio.h>  // printf
#include <stdlib.h> // srand
#include <time.h>   // time
#include "arrays.h"

#define ARR_SIZE 30

int main(void) {
  int arr[ARR_SIZE];
  int arr_c[ARR_SIZE] = {0};
  size_t min_idx, max_idx, found_idx;

  srand(time(NULL));

  initialize_array(arr, LEN(arr));
  min_idx =
      find_first(foldr(arr[0], arr, arr + LEN(arr), f_min), arr, LEN(arr));
  max_idx =
      find_first(foldr(arr[0], arr, arr + LEN(arr), f_max), arr, LEN(arr));
  found_idx = find(arr, LEN(arr));

  for (size_t i = 0; i < min_idx * 3; i++)
    putchar(' ');
  printf("v min idx: %zu\n", min_idx);
  print_array(arr, LEN(arr));
  for (size_t i = 0; i < max_idx * 3; i++)
    putchar(' ');
  printf("^ max idx: %zu\n", max_idx);
  for (size_t i = 0; i < found_idx * 3; i++)
    putchar(' ');
  printf("^ found idx: %zu\n", found_idx);
  copy(arr, arr_c, LEN(arr), LEN(arr_c));
  print_array(arr_c, LEN(arr_c));
  printf("Average val(should be near to 55), %lf", sum_average(arr, LEN(arr)));

  return 0;
}
