#include <stdio.h>

#include "proc.h"

#define LEN(arr) (sizeof(arr) / (sizeof((arr)[0])))

int main(void) {
  char res[100];
  const char *text[] = {"abcd", "bacs", "dac", "xab", "dxabssdc"};
  process(res, text, LEN(text), "b");
  puts(res);
  process(res, text, LEN(text), "x");
  puts(res);
  process(res, text, LEN(text), "bxd");
  puts(res);
  process(res, text, LEN(text), "xabcd");
  puts(res);
  process(res, text, LEN(text), "aasdasdasdas12xabcd");
  puts(res);
  return 0;
}
