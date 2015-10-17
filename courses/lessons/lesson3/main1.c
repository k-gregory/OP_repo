#include <stdio.h>
#include <math.h>

static inline int isPrime(int n){
  if(n<2) return 0;
  for(int i=2;i<sqrt(n);i++)
    if(n%i==0) return 0;
  return 1;
}

int main(void){
  for(int i=0;i<500;i++)
    if(isPrime(i)) printf("%d ",i);
}
