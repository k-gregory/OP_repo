#pragma once

#include "Element.cxx"

#include <array>

namespace io {
namespace github {
namespace atommed {
namespace linear_algebra {
  template <typename T, int dim> struct Vector {
    public:
      Vector() {
	for(std::size_t i = 0; i< dim;i++)
	  components[i] = LinearElement<T>::zero;
      }
      Vector(std::array<T,dim>&& arr) : components(arr){}
    private:
      std::array<T, dim> components;
  };
}
}
}
}
