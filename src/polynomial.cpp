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

void Polynomial::mutAdd(Polynomial* other) {
  for (size_t i = 0; i < other->coefficients.size(); i++) {
    int n = other->coefficients[i]->numerator;
    int d = other->coefficients[i]->denominator;
    if (i < coefficients.size()) {
      coefficients[i] = coefficients[i]->add(n, d);
    } else {
      coefficients.push_back(std::make_unique<Fraction>(n, d));
    }
  }
  while (!coefficients.empty() && coefficients.back()->isZero()) {
    coefficients.pop_back();
  }
}

void Polynomial::add(size_t i, int n, int d) {
  coefficients[i] = coefficients[i]->add(n, d);
}

void Polynomial::set(size_t i, int n, int d) {
  coefficients[i] = std::make_unique<Fraction>(n, d);
}

int Polynomial::getNumerator(size_t i) const {
  return coefficients[i]->numerator;
}

int Polynomial::getDenominator(size_t i) const {
  return coefficients[i]->denominator;
}
size_t Polynomial::size() const {
  return coefficients.size();
}

std::unique_ptr<Polynomial> Polynomial::add(Polynomial* other) const {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(std::max(size(), other->size()));
  for (size_t i = 0; i < size(); i++) {
    if (i >= other->size()) {
      int n = getNumerator(i);
      int d = getDenominator(i);
      result->set(i, n, d);
      continue;
    }
    int n = other->getNumerator(i);
    int d = other->getDenominator(i);
    result->add(i, n, d);
  }
  for (size_t i = size(); i < size(); i++) {
    int n = other->getNumerator(i);
    int d = other->getDenominator(i);
    result->add(i, n, d);
  }
  result->shrink();
  return result;
}

std::unique_ptr<Polynomial> Polynomial::mult(Polynomial* other) const {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(getDegree() + other->getDegree() + 1);
  for (size_t i = 0; i <= getDegree() + other->getDegree(); i++) {
    result->coefficients.push_back(std::make_unique<Fraction>(0));
  }
  for (size_t i = 0; i < coefficients.size(); i++) {
    for (size_t j = 0; j < other->coefficients.size(); j++) {
      int n = coefficients[i]->numerator;
      int d = coefficients[i]->denominator;
      int N = other->coefficients[j]->numerator;
      int D = other->coefficients[j]->denominator;
      result->coefficients[i + j] = result->coefficients[i + j]->add(n * N, d * D);
    }
  }
  result->shrink();
  return result;
}

std::unique_ptr<Monomial> Polynomial::lead() const {
  throw std::runtime_error("lead not implemented");
//  if (coefficients.empty()) {
//    return std::make_unique<Monomial>(0, 0);
//  }
//  return std::make_unique<Monomial>(coefficients.back(), getDegree());
}

void Polynomial::shrink() {
  while (!coefficients.empty() && coefficients.back()->isZero()) {
    coefficients.pop_back();
  }
}
