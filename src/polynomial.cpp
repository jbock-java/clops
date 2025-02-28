#include <iostream>
#include <sstream>

#include "polynomial.hpp"
#include "fraction.cpp"

std::string Polynomial::toString(char x) {
  std::stringstream sb;
  bool printed = false;
  for (size_t i = 0; i < coefficients.size(); i++) {
    if (coefficients[i]->isZero()) {
      continue;
    }
    if (printed) {
      sb << " + ";
    }
    printed = true;
    if (i == 0 || !coefficients[i]->isOne()) {
      sb << coefficients[i]->toString();
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

size_t Polynomial::getDegree() {
  if (coefficients.empty()) {
    return 0;
  }
  return coefficients.size();
}

std::unique_ptr<Polynomial> Polynomial::add(Polynomial* other) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(std::max(getDegree(), other->getDegree()));
  for (size_t i = 0; i < coefficients.size(); i++) {
    if (i >= other->coefficients.size()) {
      int n = coefficients[i]->numerator;
      int d = coefficients[i]->denominator;
      result->coefficients.push_back(std::make_unique<Fraction>(n, d));
      continue;
    }
    int n = other->coefficients[i]->numerator;
    int d = other->coefficients[i]->denominator;
    result->coefficients.push_back(coefficients[i]->add(n, d));
  }
  for (size_t i = coefficients.size(); i < other->coefficients.size(); i++) {
    int n = other->coefficients[i]->numerator;
    int d = other->coefficients[i]->denominator;
    result->coefficients.push_back(std::make_unique<Fraction>(n, d));
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::monoMult(Fraction* coefficient, size_t degree) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(degree + getDegree());
  for (size_t i = 0; i < degree; i++) {
    result->coefficients.push_back(std::make_unique<Fraction>(0));
  }
  for (size_t i = 0; i < getDegree(); i++) {
    int n = coefficients[i]->numerator;
    int d = coefficients[i]->denominator;
    result->coefficients.push_back(coefficient->mult(n, d));
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::mult(Polynomial* other) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(getDegree() + other->getDegree());
  for (size_t i = 0; i < other->coefficients.size(); i++) {
    Fraction* c = other->coefficients[i].get();
    std::unique_ptr<Polynomial> p = monoMult(c, i);
    result = result->add(p.get());
  }
  return result;
}
