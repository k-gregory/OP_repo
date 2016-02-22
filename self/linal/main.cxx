#include "io/github/atommed/linear_algebra/Vector.cxx"

#include <iostream>

int main() {
  using io::github::atommed::linear_algebra::Vector;
  Vector<int, 3> a({1, 2, 3});
  std::cout << a * 3 * a;
  return 0;
}
