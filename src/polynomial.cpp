#include <iostream>

#include "polynomial.hpp"

void Poly::print_polynomial(char x) {
  std::cout << x;
  for (int i = 0; i < coefficients.size(); i++) {
    std::cout << ' ' << coefficients[i];
  }
}
