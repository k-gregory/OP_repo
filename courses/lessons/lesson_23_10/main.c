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

void fillRand(int mat[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      mat[i][j] = (rand() % 2 - 1) * (rand() % 1000);
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
  int *current_left = arr;
  int *current_right = arr + length - 1;
  while (current_left < current_right) {
    while (current_left < current_right && *current_left < 0)
      current_left++;
    while (current_left < current_right && *current_right > 0)
      current_right--;
    swap_ints(current_left, current_right);
  }
}

int arr_min(int *arr, unsigned int length) {
  int res = arr[0];
  for (unsigned int i = 0; i < length; i++)
    if (res > arr[i])
      res = arr[i];
  return res;
}

int arr_max(int *arr, unsigned int length) {
  int res = arr[0];
  for (unsigned int i = 0; i < length; i++)
    if (res < arr[i])
      res = arr[i];
  return res;
}

double arr_avg(int *arr, unsigned int length) {
  double res = 0;
  for (unsigned int i = 0; i < length; i++)
    res += (arr[i] - res) / (i + 1);
  return res;
}

long long arr_sum(int *arr, unsigned int length) {
  long long res = 0;

  for (int i = 0; i < length; i++)
    res += arr[i];

  return res;
}

static inline int mat_to_arr(unsigned int row, unsigned int column,
                             unsigned int row_length) {
  row = row - 1;
  column = column - 1;
  return row * row_length + column;
}

long long arr_diagonal_sum(int *arr, unsigned int dism, unsigned int length) {
  long long res = 0;
  for (unsigned int i = 1; i <= dism; i++)
    res += arr[mat_to_arr(i, i, dism)];
  return res;
}

long long arr_subdiagonal_sum(int *arr, unsigned int dism,
                              unsigned int length) {
  long long res = 0;
  for (unsigned int i = 1; i <= dism; i++)
    res += arr[mat_to_arr(dism - i + 1, i, dism)];
  return res;
}

int main(void) {
  int a1[] = {3, 4, 5, 6, 7, -1, -6, 19, 8, 9, 15, -4, 3, 3, 10, 11, 12};
  int a2[] = {-1, 1,  40, -2, 3, 4, -7, 4, -9, 5, 6,
              2,  -1, -1, -1, 1, 1, 1,  1, -1, 1, 1};
  int m3[] = {
      -4, 3,  2,  1,  // r1
      5,  6,  -8, -8, // r2
      33, 3,  3,  1,  // r3
      -4, -4, -4, -4, // r4
  };

  puts("Task 1");
  print_n_min(a1, LEN(a1), 5);
  puts("\n");

  puts("Task 2");
  place_negatives_first(a2, LEN(a2));
  for (unsigned int i = 0; i < LEN(a2); i++)
    printf("%d ", a2[i]);
  puts("\n");

  puts("Matrix:");
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++)
      printf("%d\t", m3[mat_to_arr(i, j, 4)]);
    puts("");
  }
  puts("");

  puts("Task 3");
  printf("Min: %d, max: %d, avg: %lf, sum: %lld, mdsum: %lld, sdsum: %lld",
         arr_min(m3, LEN(m3)), arr_max(m3, LEN(m3)), arr_avg(m3, LEN(m3)),
         arr_sum(m3, LEN(m3)), arr_diagonal_sum(m3, 4, LEN(m3)),
         arr_subdiagonal_sum(m3, 4, LEN(m3)));
}
