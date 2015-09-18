#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

char result[MAX_LENGTH];
char error_ret = '\0';
char* ns_convert(char *number, unsigned int sourceBase,
                  unsigned int destBase) {
  char *current;

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

  if (fpN>0) {*current = '.';current++;};
  *current = '\0';
  return result;
}

//int ns_convert(char *number, unsigned int sourceBase, unsigned int destBase) {
//  if (*number == '\0')
//    return '\0';
//
//  if (sourceBase > 32 || sourceBase < 2 || destBase > 32 || destBase < 2)
//    return '\0';
//
//  char *result = malloc(sizeof(char) * MAX_LENGTH);
//
//  char *current = number;
//  for (; *current != '\0' && *current != '.'; current++)
//    ;
//  current--;
//
//  int integer = 0;
//  int k = 0;
//  while ((number - 1) != current) {
//    if (sourceBase < 10 && *current > '9')
//      return '\0';
//    if (*current > 'Z')
//      return '\0';
//    integer += symToInt(*current--) * pow(sourceBase, k++);
//  }
//
//  return integer;
//}

int main(void) {
  puts(ns_convert("605",16,3));
  return 0;
}
