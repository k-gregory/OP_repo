#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "arrays.h"
#include "loops.h"

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void fillRand(int arr[], size_t sz) {
  for (size_t i = 0; i < sz; i++)
    arr[i] = rand() % 100;
}

void print_arr(int arr[], size_t length) {
  for (int i = 0; i < length - 1; i++)
    printf("%d ", arr[i]);
  printf("%d\n", arr[length - 1]);
}

int main() {
  srand(time(0));
  int test_arr[30];
  fillRand3(test_arr, LEN(test_arr));
  test_arr[29] = -42;
  print_arr(test_arr, LEN(test_arr));
  printf("Check rand: %d\n", checkRand3(test_arr, LEN(test_arr)));
  printf("Mean value: %f\n", meanValue(test_arr, LEN(test_arr)));
  printf("Mean index: %d\n", meanIndex(test_arr, LEN(test_arr)));
  printf("Min value: %d\n", minValue(test_arr, LEN(test_arr)));
  printf("Min index: %d\n", minIndex(test_arr, LEN(test_arr)));
  printf("Max occurances: %d\n", maxOccurance(test_arr, LEN(test_arr)));

  int ta1[4];
  fillRand(ta1, LEN(ta1));
  print_arr(ta1, LEN(ta1));
  int ta2[4];
  fillRand(ta2, LEN(ta2));
  print_arr(ta2, LEN(ta2));
  int resa[4];
  printf("diff res: %d\n", diff(ta1, ta2, resa, LEN(resa)));
  print_arr(resa, LEN(resa));
  printf("Diff shall return 1: %d\n", diff(resa, resa, resa, LEN(resa)));
  puts("Sub:");
  print_arr(ta1, LEN(ta1));
  print_arr(ta2, LEN(ta2));
  sub(ta1, ta2, ta1, LEN(ta1));
  print_arr(ta1, LEN(ta1));
}
