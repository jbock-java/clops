#include <iostream>
#include <sstream>

#include "polynomial.hpp"

std::string Polynomial::toString(char x) {
  std::stringstream sb;
  for (size_t i = 0; i < coefficients.size(); i++) {
    if (i != 0) {
      sb << ' ';
    }
    sb << std::to_string(coefficients[i]);
  }
  return sb.str();
}

int Polynomial::getCoefficient(size_t i) {
  if (i >= coefficients.size()) {
    return 0;
  }
  return coefficients[i];
}

size_t Polynomial::getDegree() {
  if (coefficients.empty()) {
    return 0;
  }
  return coefficients.size();
}

void Polynomial::add(std::unique_ptr<Polynomial> other) {
  size_t newDegree = std::max(getDegree(), other->getDegree());
  std::vector copy = coefficients;
  coefficients.clear();
  for (size_t i = 0; i <= newDegree; i++) {
    coefficients.push_back(getCoefficient(i) + other->getCoefficient(i));
  }
}
