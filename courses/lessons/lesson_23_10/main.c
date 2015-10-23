#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct {
  int val;
  int index;
} val_and_index;

static inline int _comparator(const void *a, const void *b) {
  const val_and_index *f = a;
  const val_and_index *s = b;
  return f->val - s->val;
}

static inline void swap_ints(int *i1, int *i2) {
  int tmp = *i1;
  *i1 = *i2;
  *i2 = tmp;
}

void print_n_min(int *arr, unsigned int m, unsigned int n) {
  assert(m >= n);
  val_and_index *tmp_arr = malloc(sizeof(val_and_index) * m);
  for (unsigned int i = 0; i < m; i++) {
    val_and_index t = {arr[i], i};
    tmp_arr[i] = t;
  }
  qsort(tmp_arr, m, sizeof(val_and_index), _comparator);
  for (unsigned int i = 0; i < n; i++)
    printf("a[%d] == %d ", tmp_arr[i].index, tmp_arr[i].val);
  printf("\n");
  free(tmp_arr);
}

void place_negatives_first(int *arr, unsigned int length) {
    int* current_left = arr;
    int* current_right = arr+length-1;
    while(current_left!=current_right)
    {
        while(current_left<current_right && *current_left < 0)
            current_left++;
        while(current_left<current_right && *current_right > 0)
            current_right--;
        swap_ints(current_left,current_right);
    }
}

int main(void) {
  int a1[] = {3, 4, 5, 6, 7, -1, -6, 19, 8, 9, 15, -4, 3, 3, 10, 11, 12};
  int a2[] = {1,  40, 2,  3, 4, -7, 4, -9, 5, 6, 2,
              -1, -1, -1, 1, 1, 1,  1, -1, 1, 1};

  puts("Task 1");
  print_n_min(a1, LEN(a1), 5);

  puts("Task 2");
  place_negatives_first(a2, LEN(a2));
  for (unsigned int i = 0; i < LEN(a2); i++)
    printf("%d ", a2[i]);
  printf("\n");
}
