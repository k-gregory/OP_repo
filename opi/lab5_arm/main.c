#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void){
  int overflowed;
  printf("%d overflow:%d\n", impl(-INT_MAX,1,INT_MAX, &overflowed), overflowed);
  return EXIT_SUCCESS;
}
