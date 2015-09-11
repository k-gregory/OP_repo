#include <stdlib.h>
#include <string.h>

struct _string {
  int len;
  char *str;
};

typedef struct _string String;

String *new_String(int len) {
  String* str = malloc(sizeof(String) + sizeof(char) *len);
  str->len = len;
  str->str = (char *)(str + 1);
  return str;
}

void set_String(String *str, char *c_str_source) {
  char *curr = str->str;
  int copied = 0;
  while (*c_str_source != '\0') {
    if (copied == str->len) {
      exit(1);
    }
    *curr++ = *c_str_source;
    copied++;
  }
}

int main(int argc, char *argv[]) { 
  String *str = new_String(5);
  set_String(str,"ololo");
}
