#include <iostream>
#include <sstream>

#include "polynomial.hpp"

std::string Polynomial::toString(char x) {
  std::stringstream sb;
  for (size_t i = 0; i < coefficients.size(); i++) {
    if (i != 0) {
      sb << " + ";
    }
    if (i == 0 || coefficients[i] != 1) {
      sb << std::to_string(coefficients[i]);
    }
    if (i != 0) {
      sb << x;
    }
    if (i != 0 && i != 1) {
      sb << '^' << std::to_string(i);
    }
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

std::unique_ptr<Polynomial> Polynomial::add(std::unique_ptr<Polynomial> other) {
  Polynomial result(std::max(getDegree(), other->getDegree()));
  for (size_t i = 0; i < coefficients.size(); i++) {
    result.coefficients.push_back(coefficients[i] + other->getCoefficient(i));
  }
  for (size_t i = coefficients.size(); i < other->coefficients.size(); i++) {
    result.coefficients.push_back(other->getCoefficient(i));
  }
  return std::make_unique<Polynomial>(result);
}
