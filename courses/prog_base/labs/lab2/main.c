#include <stdio.h>

#include "arrays.h"
#include "loops.h"

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void print_arr(int arr[], size_t length) {
  for (int i = 0; i < length - 1; i++)
    printf("%d ", arr[i]);
  printf("%d\n", arr[length - 1]);
}

int main() {
  int test_arr[30];
  fillRand3(test_arr, LEN(test_arr));
  test_arr[29] = -42;
  print_arr(test_arr, LEN(test_arr));
  printf("Check rand: %d\n", checkRand3(test_arr, LEN(test_arr)));
  printf("Min value: %d\n", minValue(test_arr, LEN(test_arr)));
  printf("Min index: %d\n", minIndex(test_arr, LEN(test_arr)));
  printf("Max occurances: %d\n", maxOccurance(test_arr, LEN(test_arr)));
}
