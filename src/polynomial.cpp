#include <iostream>

#include "polynomial.hpp"

void Poly::print_polynomial(char x) {
  std::cout << x;
  for (size_t i = 0; i < coefficients.size(); i++) {
    std::cout << ' ' << coefficients[i];
  }
}

void Vary::print_polynomial(char x) {
  std::cout << x << '^' << degree;
}

void Consty::print_polynomial(char x) {
  std::cout << coefficient;
}
