#include <stdlib.h>
#include <tgmath.h>

#include "config.h"

double calc(double x, double y, double z) {
  double a0 = pow(x, y + 1.0) / pow(x - y, 1.0 / z);
  double a1 = y / ((N0 + 1.0) * fabs(x + y));
  double a2 = pow(x + N1, 1.0 / fabs(sin(y)));

  return a0 + a1 + a2;
}
