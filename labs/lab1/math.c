#include <math.h>

#define N0 5
#define N1 0

double calc(double x, double y, double z) {
  double a0 = pow(x, y + 1) / pow(x - y, 1 / z);
  double a1 = y / ((N0 + 1) * fabs(x + y));
  double a2 = pow(x + N1, 1 / fabs(sin(y)));

  return a0 + a1 + a2;
}


static inline int min3(int a, int b, int c){
  if(a>b)
    if(b>c)
      return c;
    else return b;
  else if(a>c)
    return c;
  return a;
}

int satisfies(int a, int b, int c) {

  /*First case. All nums are negative {{{*/
  if(a<0 & b<0 & c<0) {
    int modmin = abs(min3(a,b,c)); 
    int sum2 = a+b+c + modmin; /* min was negative, so vve can add module*/
  };
  /*First case }}}*/
}
