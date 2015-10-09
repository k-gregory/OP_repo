#include <stdlib.h>
#include <tgmath.h>

#include "config.h"

static inline int sizeOfNum(int a, int b) {
  size_t sz;
  switch (abs(b) % 8) {
  case 0:
    sz = sizeof(char);
    break;
  case 1:
    sz = sizeof(signed char);
    break;
  case 2:
    sz = sizeof(short);
    break;
  case 3:
    sz = sizeof(unsigned int);
    break;
  case 4:
    sz = sizeof(long);
    break;
  case 5:
    sz = sizeof(unsigned long long);
    break;
  case 6:
    sz = sizeof(float);
    break;
  case 7:
    sz = sizeof(double);
    break;
  }
  return sz * abs(a);
}

static inline int max2(int a, int b) {
  if (a > b)
    return a;
  return b;
}
static inline int min2(int a, int b) {
  if (a > b)
    return b;
  return a;
}

int exec(int op, int a, int b) {
  if (op < 0) { /* Swap a&b if op is negative*/
    int t = a;
    a = b;
    b = t;

    op = -op;
  }

  switch (op) {
  case 0:
    return -a;
    break;
  case 1:
    return a + b;
    break;
  case 2:
    return a - b;
    break;
  case 3:
    return a * b;
    break;
  case 4:
    return a / b;
    break;
  case 5:
    return abs(a);
    break;
  case 6:
    return powl(a, b);
    break;
  case 7:
  case 13:
  case 77:
    return a % b;
    break;
  case 8:
    return max2(a, b);
  case 9:
    return min2(a, b);
  case 10:
    return sizeOfNum(a, b);
    break;
  case 11:
    return (N0 + 1) * cos(b * PI) / (a - N1);
    break;
  default:
    if (op < 100)
      return (op % abs(a + 1)) + (op % abs(b + 1));
    return -1;
    break;
  }
}
