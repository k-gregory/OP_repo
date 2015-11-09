#include "impl.h"
#include <stdio.h>
/*int impl(int a, int b, int c){

}*/

int impl(int a,int b,int c){
  __asm__ __volatile__(
      "imul %0, %1\t\n"
      "sub %2, %1\t\n"
      "mov %1, %%eax"
      ::"r"(a),"r"(b),"r"(c) : "%eax"
      );
}
