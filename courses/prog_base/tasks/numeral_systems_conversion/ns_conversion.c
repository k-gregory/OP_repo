#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <tgmath.h>

#define MAX_LENGTH 64

static inline int symToInt(char ch) {
  if (ch < 'A')
    return ch - '1' + 1;
  else
    return ch - 'A' + 10;
}

int ns_convert(char *number, unsigned int sourceBase, unsigned int destBase) {

  if(*number=='\0') return '\0';

  if (sourceBase > 32 || sourceBase < 2 || destBase > 32 || destBase < 2)
    return '\0';
  
  char* current = number;
  for(;*current!='\0' && *current!='.' ;current++);
  current--;

  int sum = 0;
  int k = 0;
  while ((number-1) != current) {
    if (sourceBase < 10 && *current > '9')
      return '\0';
    if (*current > 'Z')
      return '\0';
    sum += symToInt(*current--) * pow(sourceBase, k++);
  }
  return sum;
}

int main(void) { 
 printf("%i\n", ns_convert("10110", 2, 2));
 return 0;
}
