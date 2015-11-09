#include <stdio.h>

#include "impl.h"

#define BUF_SIZE 200

int main(void) {
  char buf[BUF_SIZE];
  int a, b, c, res;
  int status;

  do {
    fgets(buf, BUF_SIZE, stdin);
    status = sscanf(buf, "%d %d %d", &a, &b, &c);
  } while (status != 3);

  __asm__ __volatile__ (
      "push %%esp\t\n"
      "mov %3, %%eax\t\n"
      "push %%eax\t\n"
      "mov %2, %%eax\t\n"
      "push %%eax\t\n"
      "mov %1, %%eax\t\n"
      "push %%eax\t\n"
      "call impl\t\n"
      "mov %%eax, %0\t\n"
      "pop %%ecx\t\n"
      "pop %%ecx\t\n"
      "pop %%ecx\t\n"
      "pop %%esp"
      :"=r"(res): "r"(a), "r"(b), "r"(c) : "%eax","%ecx"
      );
  printf("\n%d",res);
}
