#include <stdlib.h>
#include <tgmath.h>

#define N0 5
#define N1 0

double calc(double x, double y, double z) {
  double a0 = pow(x, y + 1) / pow(x - y, 1 / z);
  double a1 = y / ((N0 + 1) * fabs(x + y));
  double a2 = pow(x + N1, 1 / fabs(sin(y)));

  return a0 + a1 + a2;
}

static inline int isPowOf2(int x) { return (x & x - 1) == 0; }

static inline int min3(int a, int b, int c) {
  if (a > b)
    if (b > c)
      return c;
    else
      return b;
  else if (a > c)
    return c;
  return a;
}

static inline int max3(int a, int b, int c) {
  if (a > b) {
    if (a > c)
      return a;
    else
      return c;
  }
  if (b > c)
    return b;
  return c;
}

int satisfies(int a, int b, int c) {

  /*First case. All nums are negative {{{*/
  if (a < 0 && b < 0 && c < 0) {
    int modmin = abs(min3(a, b, c));
    int sum2 = a + b + c + modmin;

    if (sum2 < -256 && modmin < 256 && isPowOf2(modmin)) {
      return 1;
    }

    if (abs(sum2) > modmin && sum2 > -256)
      return 1;
    return 0;
  };
  /*First case }}}*/

  /*Third case. All nums are positive {{{*/
  if (a >= 0 && b >= 0 && c >= 0) {
    int min = min3(a, b, c);
    int max = max3(a, b, c);

    return (max - min) > 32;
  }
  /*Third case. }}} */

  /*Second case. Some nums are positive {{{*/
  int min = min3(a, b, c);
  int max = max3(a, b, c);
  int avg =
      a + b + c - min - max; /* avg is the second number if we sort a,b,c  */
  if (avg < 0)
    return (min + avg) * N0 * N1 > -256; /* avg<0, so 2 nums are negative */
  return min > -256; /*avg is > 0, so only one num is negative */
                     /*Second case }}}*/
}

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
  default:
    if (op < 100)
      return (op % abs(a + 1)) + (op % abs(b + 1));
    return -1;
  }
}
