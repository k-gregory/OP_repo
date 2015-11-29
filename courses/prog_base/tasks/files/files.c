#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VARIANT 5
#define MAX_STR_LENGTH 300
#define MAX_WORD 17

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void fprocess(const char *in_name, const char *of_name) {
  char buffer[MAX_STR_LENGTH];
  char word[MAX_WORD];
  size_t len = MAX_WORD;
  FILE *f = fopen(in_name, "r");
  for (size_t i = 0; i < VARIANT; i++)
    fgets(buffer, LEN(buffer),f);
  fclose(f);
  char *w = strtok(buffer, " ");
  while (w != NULL) {
    if (len > strlen(w)) {
      len = strlen(w);
      strcpy(word, w);
    }
    w = strtok(NULL, " ");
  }

  f = fopen(of_name, "w");
  fputs(word,f);
  fclose(f);
}
