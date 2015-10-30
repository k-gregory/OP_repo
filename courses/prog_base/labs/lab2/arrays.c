#include <stdlib.h>
#include <math.h>
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

float meanValue(int arr[], size_t sz) {
  float res = 0;
  for (size_t i = 0; i < sz; i++) {
    res += (arr[i] - res) / (1 + i);
  }
  return res;
}

int meanIndex(int arr[], size_t sz) {
  float mean = meanValue(arr, sz);
  int *mean_index = &arr[0];
  for (size_t i = 1; i < sz; i++)
    if (fabs(mean - *mean_index) > fabs(mean - arr[i]))
      mean_index = &arr[i];
  return mean_index - arr;
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

int diff(int arr1[], int arr2[], int res[], size_t sz) {
  for (size_t i = 0; i < sz; i++) {
    int t = arr1[i] - arr2[i];
    res[i] = t;
    if (t != 0) {
      for (size_t j = i + 1; j < sz; j++)
        res[j] = arr1[j] - arr2[j];
      return 0;
    }
  }
  return 1;
}

void sub(int arr1[], int arr2[], int res[], size_t sz) {
  diff(arr1, arr2, res, sz);
}

int eq(int arr1[], int arr2[], size_t sz){
  for(size_t i = 0; i<sz;i++)
    if(arr1[i]!=arr2[i])
      return 0;
  return 1;
}

void land(int arr1[], int arr2[], int res[], size_t sz){
  for(size_t i = 0; i<sz;i++)
    res[i] = arr1[i] & arr2[i];
}
