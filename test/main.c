#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct _string {
  int len;
  char *str;
};

typedef struct _string String;

String *new_String(int len) {
  String *str = malloc(sizeof(String) + sizeof(char) * len);
  str->len = len;
  str->str = (char *)(str + 1);
  return str;
}

void free_String(String *p) { free(p); }

bool copy_String(String *dest, String *source) {
  if (dest->len < source->len)
    return false;
  for (int i = 0; i < source->len; i++) {
    dest->str[i] = source->str[i];
  }
  return true;
}

bool set_String(String *str, char *c_str_source) {
  char *curr = str->str;
  int copied = 0;
  while (*c_str_source != '\0') {
    if (copied == str->len) {
      puts("String is n0t l0ng en0ughth");
      return false;
    }
    *curr++ = *c_str_source++;
    copied++;
  }
  return true;
}

int main(int argc, char *argv[]) {
  String *str = new_String(5);
  set_String(str, "ololo");
  for (int i = 0; i < 5; i++)
    printf("%c", str->str[i]);
  free_String(str);
}
