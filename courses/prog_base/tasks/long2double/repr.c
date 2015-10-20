#include "repr.h"

#include <stdio.h>
#include <math.h>

static const int ll_size_equals_double_size_check =
    1 / ((sizeof(double) - sizeof(long long)) == 0);

double hack_long2double(long long x) { return *((double *)&x); }

static inline int nth_bit(long long num, int n) {
  return (num & (1LL << (64 - n))) != 0; // 1LL << (64 - n);
}

double long2double(long long x) {
  char buff[1024];
  double res;
  sprintf(buff, "%lld", x);
  sscanf(buff, "%lld", &res);
  return res;
}

double algoritmic_long2double(long long x) {
  double sign = nth_bit(x, 1) ? -1 : 1;
  double mantissa = 0;
  double exp = 0;

  int p = 1;
  for (int i = 12; i > 1; i--) {
    exp += nth_bit(x, i) * p;
    p *= 2;
  }

  double pw = 0.5;
  for (int i = 13; i <= 64; i++) {
    mantissa += nth_bit(x, i) * pw;
    pw /= 2;
  }

  if (exp == 2047) {
    if (mantissa != 0.0)
      return NAN;
    if (sign > 0)
      return INFINITY;
    return -INFINITY;
  }
  if (exp == 0) {
    if (mantissa != 0)
      return sign * pow(2, -1022) * mantissa;
    if (sign > 0)
      return 0;
    return -0.0;
  }
  return sign * pow(2, exp - 1023) * (mantissa + 1);
}
