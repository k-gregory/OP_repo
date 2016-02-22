#include <stdio.h>

int max(int *arr, int n) {
  int max = arr[0];
  for (int i = 0; i < n; i++)
    if (max < arr[i])
      max = arr[i];
  return max;
}

int arr[] = {1, 2, 3, 5, 7, 11, 2, 13, 1};

int main(void) { printf("%d", max(arr, 9)); }
