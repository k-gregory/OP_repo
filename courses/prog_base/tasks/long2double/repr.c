#include "repr.h"

#include <stdio.h>
#include <assert.h>

static const int ll_size_equals_double_size_check =
    1 / ((sizeof(double) - sizeof(long long)) == 0);

double hack_long2double(long long x){
  assert(sizeof(double)==sizeof(long long));
  return *((double*)&x);
}

double long2double(long long x){
  char buff[1000];
  sprintf(buff,"%f",x);
  double res;
  sscanf(buff,"%lf",&res);
  return res;
}

#define nth_byte(num,n) ((num))&(1<<(n))

/*double long2double(long long x){
}*/
