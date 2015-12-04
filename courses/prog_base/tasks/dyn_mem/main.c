#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define STRING_MAX 100

int main(void) {

  char *str = malloc(STRING_MAX);
  char *fr = str;
  char *last = "0";
  fgets(str, STRING_MAX, stdin);
  while (*str++) {
    if (isdigit(*str))
      last = str;
  };

  printf("%c is the last digit\n", *last);

  free(fr);
  return EXIT_SUCCESS;
}
