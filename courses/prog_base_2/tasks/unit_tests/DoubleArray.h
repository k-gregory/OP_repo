#pragma once

#include <stdlib.h>

typedef struct DoubleArray DoubleArray;

DoubleArray* DoubleArray_new(size_t size);
DoubleArray* DoubleArray_new_with_zeroes(size_t size);
void DoubleArray_delete(DoubleArray* arr);
/*Add #define DOUBLE_ARRAY_NO_INDEX_CHECK
  as compiler option to avoid index check*/
double* DoubleArray_at(DoubleArray* arr, size_t index);
size_t DoubleArray_size(DoubleArray* arr);

double DoubleArray_min(const DoubleArray* arr);
double DoubleArray_max(const DoubleArray* arr);
double DoubleArray_max_by(const DoubleArray* arr,
			    int (*double_cmp)(double a, double b));
int DoubleArray_contains(const DoubleArray* arr, double element);

double DoubleArray_min_l(const DoubleArray* arr, size_t last);
double DoubleArray_max_l(const DoubleArray* arr, size_t last);
double DoubleArray_max_by_l(const DoubleArray* arr,
			    int (*double_cmp)(double a, double b),size_t last);
int DoubleArray_contains_l(const DoubleArray* arr, double element,size_t last);
