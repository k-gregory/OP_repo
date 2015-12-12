#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

static inline int is_consonant(int letter) {
  if (!islower(letter) && !isupper(letter))
    return 0;
  switch (tolower(letter)) {
  case 'e':
  case 'y':
  case 'u':
  case 'i':
  case 'o':
  case 'a':
    return 0;
    break;
  }
  return 1;
}

void tolower_string(char *str) {
  for (size_t i = 0; i < strlen(str); i++)
    str[i] = tolower(str[i]);
}

void print_unique_letters(const char *str, FILE *stream) {
  int letters[CHAR_MAX - CHAR_MIN] = {0};
  for (size_t i = 0; i < strlen(str); i++)
    letters[str[i] - CHAR_MIN] = 1;
  for (size_t i = 0; i < LEN(letters); i++)
    if(letters[i] && is_consonant(i+CHAR_MIN))
      fprintf(stream, "%c ", i + CHAR_MIN);
}

int main(int argc, char *argv[]) {
  FILE *f;
  char buff[1024];
  if (argc != 2) {
    fprintf(stderr, "Usage: %s filename", argv[0]);
    return EXIT_FAILURE;
  }
  f = fopen(argv[1], "w");

  puts("Please, enter your string");
  fgets(buff, LEN(buff), stdin);

  tolower_string(buff);
  printf("Lowered string: %s", buff);

  print_unique_letters(buff, f);


  fclose(f);
  return EXIT_SUCCESS;
}
