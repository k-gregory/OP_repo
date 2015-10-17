#include "repr.h"

#include <stdio.h>
#include <assert.h>

double hack_long2double(long long x){
  assert(sizeof(double)==sizeof(long long));
  return *((double*)&x);
}

#define nth_byte(num,n) ((num))&(1<<(n))

double long2double(long long x){
  return nth_byte(x,1);
}
