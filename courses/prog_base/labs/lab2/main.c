#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "arrays.h"
#include "loops.h"
#include "automata.h"

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void fillRand(int arr[], size_t sz) {
  for (size_t i = 0; i < sz; i++)
    arr[i] = rand() % 100;
}

void print_arr(int arr[], size_t length) {
  if (length == 0)
    return;

  for (size_t i = 0; i < length - 1; i++)
    printf("%d ", arr[i]);
  printf("%d\n", arr[length - 1]);
}

void test_automata(int moves[], size_t moves_len, int res[], size_t res_len) {
  size_t n = run(moves, moves_len, res, res_len);
  puts("Input:");
  print_arr(moves, moves_len);
  puts("Output:");
  print_arr(res, n);
  puts("");
}

int main() {
  puts("Test loops");
  printf("calc(2,1): %lf \n", calc(2, 1));
  printf("calc(42,15): %lf \n\n", calc(42, 15));

  puts("Test arrays");
  srand(time(0));
  int test_arr[30];
  fillRand3(test_arr, LEN(test_arr));
  print_arr(test_arr, LEN(test_arr));
  fillRand3(test_arr, LEN(test_arr));
  test_arr[29] = -42;
  print_arr(test_arr, LEN(test_arr));
  printf("Check rand: %d\n", checkRand3(test_arr, LEN(test_arr)));
  printf("Mean value: %f\n", meanValue(test_arr, LEN(test_arr)));
  printf("Mean index: %d\n", meanIndex(test_arr, LEN(test_arr)));
  printf("Min value: %d\n", minValue(test_arr, LEN(test_arr)));
  printf("Min index: %d\n", minIndex(test_arr, LEN(test_arr)));
  printf("Max occurances: %d\n", maxOccurance(test_arr, LEN(test_arr)));

  puts("\nOperations on 2 arrays:");
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

  /*AUTOMATA*/
  puts("");
  puts("Testing automata");
  int res[1000];
  int m1[] = {1, 2, 3, 4, 5, 6};
  int m2[] = {10, 105, 10};
  int m3[] = {105, 105, 105, 105, 105, 105, 105};
  int m4[] = {10, 105, 105, 105, 105, 105, 5};
  test_automata(m1, LEN(m1), res, LEN(res));
  test_automata(m2, LEN(m2), res, LEN(res));
  test_automata(m3, LEN(m3), res, LEN(res));
  test_automata(m3, LEN(m3), res, 3);
  test_automata(m4, LEN(m4), res, LEN(res));
  return 0;
}
