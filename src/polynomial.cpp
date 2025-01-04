#include <iostream>

#include "polynomial.hpp"

void Poly::print_polynomial() {
  std::cout << name;
  for (int i = 0; i < coefficients.size(); i++) {
    std::cout << ' ' << coefficients[i];
  }
}
