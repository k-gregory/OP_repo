#include <stdio.h>

typedef unsigned long long uint;

int main(void){
  uint n;
  uint res=1;
  uint fact=1;
  scanf("%lld",&n);
  for(uint i=1;i<=n;i++){
    fact*=i;
    res*=fact;
  }
  printf("%lld",res);
}
