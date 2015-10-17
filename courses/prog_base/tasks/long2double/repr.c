#include "repr.h"

#include <assert.h>
#include <math.h>

static const int ll_size_equals_double_size_check =
    1 / ((sizeof(double) - sizeof(long long)) == 0);

double hack_long2double(long long x) { return *((double *)&x); }

#define nth_byte(num, n) (((((num)) & (1LL << (64 - n))) > 0))

double long2double(long long x) {
  double mantissa = 1;
  unsigned int exp = 0;

  int sign = nth_byte(x, 1) ? -1 : 1;

  int p = 1;
  for (int i = 12; i > 1; i--) {
    exp += nth_byte(x, i) * p;
    p *= 2;
  }
  double pw = 0.5;
  for (int i = 13; i <= 64; i++) {
    mantissa += nth_byte(x, i) * pw;
    pw /= 2;
  }
  /*EXP==2047*/
  if (exp == 0b11111111111) {
    if (mantissa != 0)
      return NAN;
    if (sign > 0)
      return INFINITY;
    return -INFINITY;
  }
  if (exp == 0) {
    if (mantissa != 0)
      return sign * pow(2, -1022) * (mantissa - 1);
    if (sign > 0)
      return 0;
    return -0.0;
  }
  return sign * pow(2, exp - 1023) * mantissa;
}
