/*#include <stdio.h>

int main(void){
  printf("char is %i\n",sizeof(char));
  printf("int is %i\n",sizeof(int));
  printf("pointer is %i\n",sizeof(void*));
  return 0;
}*/

int main(){
  char a[] = {1,2,5,3};
  void (*foo)(void) = a;
  foo();
}
