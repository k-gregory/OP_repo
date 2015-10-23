#include "config.h"

#include <math.h>

static inline double sum1(const int i, const int m);

double calc(const int n,const int m){
  double res = 0;
  for(int i = 1; i< n; i++)
      res+=cos(M_PI/i)*sum1(i,m);
  return res;
}

static inline double sum1(const int i,const int m){
  double res = 0;
  for(int j = 1; j<m;j++)
    res+=((double)i)/(j+N1);
  return res;
}
