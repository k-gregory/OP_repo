#include "DoubleArray.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
  DoubleArray* da = DoubleArray_new(10);
  for(size_t i  = 0; i< DoubleArray_size(da); i++)
    *DoubleArray_at(da,i) = i % 7;
  *DoubleArray_at(da, 0) = 5;
  *DoubleArray_at(da,9) = 42;
  printf("%lf %lf %d",
	 DoubleArray_min(da),
	 DoubleArray_max(da),
	 DoubleArray_contains(da,4));
  DoubleArray_delete(da);
  return EXIT_SUCCESS;
}
