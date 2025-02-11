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
  std::vector<int> copy = coefficients;
  for (size_t i = 0; i < coefficients.size(); i++) {
    coefficients[i] = copy[i] + other->getCoefficient(i);
  }
  for (size_t i = coefficients.size(); i < other->coefficients.size(); i++) {
    coefficients.emplace_back(other->coefficients[i]);
  }
}
