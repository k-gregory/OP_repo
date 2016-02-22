#include <stdio.h>

int lop1() {
  int count = 0;
  for (int i = 103; i < 987; i++) {
    int k = i;
    int a = k % 10;
    k = k / 10;
    int b = k % 10;
    k = k / 10;
    int c = k % 10;
    if (a != b && a != c && b != c)
      count++;
  }
  return count;
}
int main(void) { printf("%d\n", lop1()); }
