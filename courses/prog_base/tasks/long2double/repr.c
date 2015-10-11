#include <stdio.h>
#include <assert.h>

double long2double(long long x){
  assert(sizeof(double)==sizeof(long long));
  return *((double*)&x);
}

int main(){

  long long a = 20;

  printf("%.30f, %.30f\n",
      long2double(4620000000000000000),
      long2double(-4620000000000000000));

  return 0;
}
