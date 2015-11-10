#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arrays.h"

int main(void) {
  srand(time(NULL));
  int arr[30];
  int arr_c[30] = {0};
  size_t min_idx, max_idx, found_idx;
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
}
