#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

char rf(const char* str, char current){
  if(*str=='\0')
    return current;
  if(*str=='@')
    current = *(str+1);
  return rf(str+1, current);
}

int main(void){
  char buffer[1024];
  fgets(buffer, LEN(buffer), stdin);
  printf("%c", rf(buffer,'0'));
  return EXIT_SUCCESS;
}
