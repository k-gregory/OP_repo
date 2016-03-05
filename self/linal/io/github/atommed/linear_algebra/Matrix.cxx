#pragma once

#include "Vector.cxx"

#include <array>

namespace io {
namespace github {
namespace atommed {
namespace linear_algebra {
/** Matrix has M rows and N columns **/
template <typename T, int M, int N> struct Matrix {
  using Row = Vector<T,N>;
  public:
  Matrix(std::array<Row, M>&& _rows) : rows(_rows) {}
  private:
    std::array<Row,M> rows;
};
}
}
}
}
