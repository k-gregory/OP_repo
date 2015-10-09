#include <stdlib.h>
#include <tgmath.h>

#include "config.h"

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
