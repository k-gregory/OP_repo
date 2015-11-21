#include <stdio.h>

int main(void) {
  for (int i = 0;; i++)
    putchar(((i * (i >> 17 | i >> 9) & 46 & i >> 3)) ^
            (i & i >> 10 | i >> 100));
}
