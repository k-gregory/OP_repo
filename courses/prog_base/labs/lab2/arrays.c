#include <stdlib.h>
#include <limits.h>

#include "arrays.h"

void fillRand3(int arr[], size_t sz) {
  for (size_t i = 0; i < sz; i++)
    arr[i] = rand() % 2;
}

int checkRand3(int arr[], size_t sz) {
  for (size_t i = 0; i < sz; i++)
    if (arr[i] != 0)
      if (arr[i] != 1)
        return 0;
  return 1;
}

int minValue(int arr[], size_t sz) {
  int min = arr[0];
  for (size_t i = 0; i < sz; i++)
    if (arr[i] < min)
      min = arr[i];
  return min;
}

int minIndex(int arr[], size_t sz) {
  int *min = &arr[0];
  for (size_t i = 0; i < sz; i++)
    if (arr[i] < *min)
      min = &arr[i];
  return min - arr;
}

int maxOccurance(int arr[], size_t sz) {
  int *elems = malloc(sizeof(int) * sz);
  int *occurances = malloc(sizeof(int) * sz);
  int last_index = 0;

  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++) {
      if (j == last_index) {
        elems[last_index] = arr[i];
        occurances[last_index] = 1;
        last_index++;
        break;
      }
      if (elems[j] == arr[i]) {
        occurances[j]++;
        break;
      }
    }
  int max_val = occurances[0];
  int max_index = 0;
  for (size_t i = 0; i < last_index; i++)
    if (occurances[i] > max_val) {
      max_val = occurances[i];
      max_index = i;
    }
  return elems[max_index];
}
