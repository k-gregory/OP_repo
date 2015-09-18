#include <stdio.h>
#include <tgmath.h>

#define MAX_LENGTH 64

static inline int symToInt(char ch) {
  if (ch < 'A')
    return ch - '1' + 1;
  else
    return ch - 'A' + 10;
}

static inline char intToSym(int s) {
  if (s < 10)
    return '1' + s - 1;
  else
    return 'A' + s - 10;
}

char result[MAX_LENGTH+1];
char error_ret = '\0';
char* ns_convert(char *number, unsigned int sourceBase,
                  unsigned int destBase) {
  char *current;
  int neg = 0;
  if(*number == '-'){
    neg = 1;
    number++;
  }

  if (*number == '\0' || sourceBase < 2 || sourceBase > 32 || destBase < 2 ||
      destBase > 32)
    return &error_ret;

  int ipN = 0; //
  int fpN = 0; // integer/fractional part symbol count

  int *c = &ipN;

  for (current = number; *current != '\0'; current++) {
    if (sourceBase < 10 && *current > '9')
      return &error_ret;
    else if (*current > 'Z')
      return &error_ret;
    if (*current == '.') {
      c = &fpN;
      continue;
    }
    (*c)++;
  }


  current = number;
  int numI = 0;
  double numD = 0;
  for (int i = ipN - 1; i >= 0; i--) {
    numI += symToInt(*current++) * powl(sourceBase, i);
  }

  current++;

  for(int i = 1; i <= fpN; i++) {
    numD += symToInt(*current++) * pow(sourceBase, -i);
  }


  current = result;
  while(numI!=0){
   *(current++) = intToSym(numI % destBase); 
   numI/=destBase;
  }

  char* b;char* e;
  for(b=result,e = current -1;b<e;b++,e--){
    char t = *b;
    *b = *e;
    *e = t;
  }

  *current = '\0';

  if (fpN>0) 
    *current = '.';
  else return result;
  current++;
 
  double integral;
  for(int i = 0; i<12;i++){
    numD = modf(numD*destBase,&integral);
    *(current++) = intToSym(integral);
    if(numD == 0) break;
  }

  return result;
}

int main(void) {
  puts(ns_convert("60EA4.54DF",16,25));
  return 0;
}
