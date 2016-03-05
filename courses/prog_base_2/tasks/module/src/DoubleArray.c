#include "DoubleArray.h"

#include <stdlib.h>
#include <string.h>

struct DoubleArray {
  size_t size;
  double data[];
};

DoubleArray* DoubleArray_new(size_t size){
  if(size < 1) return NULL;
  DoubleArray* ret = malloc(sizeof(DoubleArray) + sizeof(double) * size);
  ret->size = size;
  return ret;
}

DoubleArray* DoubleArray_new_with_zeroes(size_t size){
  DoubleArray* ret = DoubleArray_new(size);
  if(ret==NULL) return ret;
  for(size_t i = 0; i < size ; i++)
    ret->data[i] = 0;
  return ret;
}

void DoubleArray_delete(DoubleArray* arr){
  free(arr);
}

size_t DoubleArray_size(DoubleArray* arr){
  return arr->size;
}

double* DoubleArray_at(DoubleArray* arr, size_t index){
  #ifndef DOUBLE_ARRAY_NO_INDEX_CHECK
  if(arr->size <= index){
    return NULL;
  }
  #endif
  return arr->data + index;
}

double DoubleArray_min(const DoubleArray* arr){
  return DoubleArray_min_l(arr, 0);
}

double DoubleArray_min_l(const DoubleArray* arr, size_t last){
  if(last == 0 || last > arr->size)
    last = arr->size;
  double c_min = arr->data[0];
  for(size_t i = 1; i < last;i++)
    if(arr->data[i] < c_min)
      c_min = arr->data[i];
  return c_min;
}

double DoubleArray_max(const DoubleArray* arr) {
  return DoubleArray_max_l(arr, 0);
}

double DoubleArray_max_l(const DoubleArray* arr, size_t last){
  if(last == 0 || last > arr->size)
    last = arr->size;
  double c_max = arr->data[0];
  for(size_t i = 1; i < last;i++)
    if(arr->data[i] > c_max)
      c_max = arr->data[i];
  return c_max;
}

double DoubleArray_max_by(const DoubleArray* arr, int (*double_cmp)(double a, double b)){
  return DoubleArray_max_by_l(arr,0,double_cmp);
}

double DoubleArray_max_by_l(const DoubleArray* arr, size_t last,
			  int (*double_cmp)(double a, double b)){
  if(last == 0 || last > arr->size)
    last = arr->size;
  double c_max = arr->data[0];
  for(size_t i = 1; i < last;i++)
    if(double_cmp(arr->data[i],c_max) > 0)
      c_max = arr->data[i];
  return c_max;
}

int DoubleArray_contains(const DoubleArray* arr, double element) {
  return DoubleArray_contains_l(arr, 0, element);
}

int DoubleArray_contains_l(const DoubleArray* arr, size_t last, double element){
  if(last == 0 || last > arr->size)
    last = arr->size;
  for(size_t i = 0; i < arr->size;i++)
    if(arr->data[i] == element)
      return 1;
  return 0;
}
