#include <stdio.h>
#include <assert.h>
#include "Stack.h"

int main(void){
  Stack* s  = alloc_Stack(2);
  push(s,2);
  assert(pop(s)==2);
  push(s,2);
  push(s,5);
  assert(pop(s)==5);
  push(s,2);
  push(s,1);
  push(s,6);
  assert(pop(s)==6);
  push(s,7);
  print_Stack(s);
  free_Stack(s);
}
