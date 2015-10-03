#include <stdio.h>

enum error { NOT_FOUND = 404, SERVER_ERRO = 500, INVALID_OPERATION = 505 };

int main() {
  int i = 3;

  switch (i) {
  case 0:
    puts("Nol");
    break;
  case 1:
    puts("Odin");
    break;
  case 77:
  case 777:
  case 7777:
    puts("Bingo!");
    break;
  default:
    puts("Error");
    break;
  }
}
