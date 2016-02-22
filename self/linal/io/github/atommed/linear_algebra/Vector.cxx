#pragma once

#include "Element.cxx"

#include <iostream>
#include <utility>
#include <array>

namespace io {
namespace github {
namespace atommed {
namespace linear_algebra {
template <typename T, int dim> struct Vector {
public:
  Vector() {
    for (std::size_t i = 0; i < dim; i++)
      components[i] = LinearElement<T>::zero;
  }
  Vector(std::array<T, dim> &&arr) : components(arr) {}

  T &operator[](const std::size_t idx) { return components[idx]; }
  const T &operator[](const std::size_t idx) const { return components[idx]; }

  /** Scalar multiplication of vectors **/
  template <typename T2> auto operator*(const Vector<T2, dim> v2) const {
    using std::declval;
    using multType = decltype(declval<T>() * declval<T>());
    using sumType = decltype(declval<multType>() + declval<multType>());

    sumType sum = LinearElement<sumType>::zero;
    for (std::size_t i = 0; i < dim; i++)
      sum += (*this)[i] * v2[i];

    return sum;
  }

  /** Multiply vector by scalar **/
  template <typename Scalar> Vector<T, dim> operator*(const Scalar x) const {
    // TODO: Can returned vector contain elements of other type?
    // TODO: RVO?
    Vector<T, dim> ret;

    for (std::size_t i = 0; i < dim; i++)
      ret[i] = (*this)[i] * x;

    return ret;
  }

private:
  std::array<T, dim> components;
};
}
}
}
}
