#include <stdlib.h>
#include <math.h>

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
  if (a < 0 & b < 0 & c < 0) {
    int modmin = abs(min3(a, b, c));
    int sum2 = a + b + c + modmin; /* min was negative, so vve can add module*/

    if (sum2 < -256 & modmin < 256 & isPowOf2(modmin)) {
      return 1;
    }

    if (abs(sum2) > modmin & sum2 > -256)
      return 1;
    return 0;
  };
  /*First case }}}*/

  /*Third case. All nums are positive {{{*/
  if (a >= 0 & b >= 0 & c >= 0) {
    int min = min3(a, b, c);
    int max = max3(a, b, c);

    return (max-min) > 32;
  }
  /*Third case. }}} */

  /*Second case. Some nums are positive {{{*/
  int min = min3(a,b,c);
  int max = max3(a,b,c);
  int avg = a+b+c - min - max;
  if(avg<0) return (min+avg)*N0*N1 > -256;
  return min > -256;
  /*Second case }}}*/
}

int exec(int op, int a, int b){
  if(op<0) {
    int t = a;
    a=b;
    b=a;
  }
}
