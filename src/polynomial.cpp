#include <iostream>
#include <sstream>

#include "polynomial.hpp"
#include "fraction.cpp"

std::string Polynomial::toString(char x) const {
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

size_t Polynomial::getDegree() const {
  if (coefficients.empty()) {
    return 0;
  }
  return coefficients.size() - 1;
}

std::unique_ptr<Polynomial> Polynomial::add(Polynomial* other) const {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(std::max(coefficients.size(), other->coefficients.size()));
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
  while (!result->coefficients.empty() && result->coefficients.back()->isZero()) {
    result->coefficients.pop_back();
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::monoMult(Fraction* coefficient, size_t degree) const {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(degree + coefficients.size());
  for (size_t i = 0; i < degree; i++) {
    result->coefficients.push_back(std::make_unique<Fraction>(0));
  }
  for (size_t i = 0; i < coefficients.size(); i++) {
    int n = coefficients[i]->numerator;
    int d = coefficients[i]->denominator;
    result->coefficients.push_back(coefficient->mult(n, d));
  }
  while (!result->coefficients.empty() && result->coefficients.back()->isZero()) {
    result->coefficients.pop_back();
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::mult(Polynomial* other) const {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(coefficients.size() + other->coefficients.size());
  for (size_t i = 0; i < other->coefficients.size(); i++) {
    Fraction* c = other->coefficients[i].get();
    std::unique_ptr<Polynomial> p = monoMult(c, i);
    result = result->add(p.get());
  }
  while (!result->coefficients.empty() && result->coefficients.back()->isZero()) {
    result->coefficients.pop_back();
  }
  return result;
}

std::unique_ptr<Monomial> Polynomial::lead() const {
  throw std::runtime_error("lead not implemented");
//  if (coefficients.empty()) {
//    return std::make_unique<Monomial>(0, 0);
//  }
//  return std::make_unique<Monomial>(coefficients.back(), getDegree());
}
