#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef int f_cmp(void *a, void *b);
typedef void f_swap(void *a, void *b);

int cmp_ints(void *a, void *b) { return (int *)a - (int *)b; }

void swap_ints(void *a, void *b) {
  int t = *(int *)a;
  *(int *)a = *(int *)b;
  *(int *)b = t;
}

void my_sort(void *arr, size_t el_count, size_t el_size, f_cmp cmp_cb,
             f_swap swap_cb) {
  for (int i = 0; i < el_count - 1; i++)
    for (int j = 0; j < el_count - i - 1; j++) {
      void *curr = (char *)arr + el_size * j;
      void *next = (char *)arr + el_size * (j + 1);
      if (cmp_cb(curr, next))
        swap_cb(curr, next);
    }
}

void view_arr(int *arr, size_t el_count) {
  for (int i = 0; i < el_count; i++)
    printf("%d ", arr[i]);
  puts("");
}

int main(void) {
  int arr[] = {1, 54,  3,  32, 32, 21, 34, 6,  2,
               3, 342, 23, 1,  23, 23, 55, 62, 3};
  view_arr(arr, LEN(arr));
  my_sort(arr, LEN(arr), sizeof(int), cmp_ints, swap_ints);
  view_arr(arr, LEN(arr));
  return EXIT_SUCCESS;
}
