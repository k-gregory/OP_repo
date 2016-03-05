#include "io/github/atommed/linear_algebra/Vector.cxx"
#include "io/github/atommed/linear_algebra/Matrix.cxx"

#include <iostream>

int main() {
  using io::github::atommed::linear_algebra::Vector;
  using io::github::atommed::linear_algebra::Matrix;
  Vector<int, 2> a({1, 2});
  Matrix<int,2,2> p({a*3,a});
  Matrix<int,2,2> m({{{1,2},{3,4}}});
  std::cout << a * 3 * a;
  return 0;
}
