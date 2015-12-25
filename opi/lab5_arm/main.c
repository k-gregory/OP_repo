#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define BUFF_LEN 50
#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

int main(void){
  int overflowed;
  char buff[BUFF_LEN];
  int a,b,c;
  printf("INT_MIN: %d\n", INT_MIN);

  do {
    puts("Enter \"a b c\"");
    fgets(buff, LEN(buff), stdin);
  } while(sscanf(buff,"%d %d %d",&a, &b, &c)!=3);

  printf("a*b-c=%d overflow:%d\n", impl(a,b,c, &overflowed), overflowed);
  return EXIT_SUCCESS;
}
