#include <stdio.h>
#include <assert.h>

union {
  double d;
  long long ll;
} caster;

double no_ptr_casts_but_unfair_long2double(long long x) {
  caster.ll = x;
  return caster.d;
}

static const int ll_size_equals_double_size_check =
    1 / ((sizeof(double) - sizeof(long long)) == 0);
