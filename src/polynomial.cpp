#include <iostream>
#include <sstream>
#include <numeric>

#include "polynomial.hpp"
#include "fraction.cpp"

std::string Polynomial::toString(char x) const {
  std::stringstream sb;
  bool printed = false;
  for (size_t i = 0; i < size(); i++) {
    int numerator = coefficients[2 * i];
    int denominator = coefficients[2 * i + 1];
    bool isZero = numerator == 0;
    bool isOne = numerator == denominator;
    if (isZero) {
      continue;
    }
    if (printed) {
      sb << " + ";
    }
    printed = true;
    if (i == 0 || !isOne) {
      if (denominator == 1) {
        sb << std::to_string(numerator);
      } else {
        sb << std::to_string(numerator) + "/" + std::to_string(denominator);
      }
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
  return (coefficients.size() / 2) - 1;
}

void Polynomial::mutAdd(Polynomial* other) {
  for (size_t i = 0; i < other->size(); i++) {
    int n = other->getNumerator(i);
    int d = other->getDenominator(i);
    add(i, n, d);
  }
  shrink();
}

void Polynomial::add(size_t i, int numerator, int denominator) {
  int diff = i - size() + 1;
  for (int j = 0; j < diff; j++) {
    coefficients.push_back(0);
    coefficients.push_back(1);
  }
  int n = coefficients[2 * i];
  int d = coefficients[2 * i + 1];
  int n2 = numerator * d + denominator * n;
  int d2 = denominator * d;
  int divisor = std::gcd(n2, d2);
  coefficients[2 * i] = n2 / divisor;
  coefficients[2 * i + 1] = d2 / divisor;
}

void Polynomial::set(size_t i, int numerator, int denominator) {
  int diff = i - size() + 1;
  for (int j = 0; j < diff; j++) {
    coefficients.push_back(0);
    coefficients.push_back(1);
  }
  int divisor = std::gcd(numerator, denominator);
  coefficients[2 * i] = numerator / divisor;
  coefficients[2 * i + 1] = denominator / divisor;
}

int Polynomial::getNumerator(size_t i) const {
  return coefficients[2 * i];
}

int Polynomial::getDenominator(size_t i) const {
  return coefficients[2 * i + 1];
}

size_t Polynomial::size() const {
  return coefficients.size() / 2;
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
  for (size_t i = 0; i < size(); i++) {
    for (size_t j = 0; j < other->size(); j++) {
      int n = getNumerator(i);
      int d = getDenominator(i);
      int N = other->getNumerator(j);
      int D = other->getDenominator(j);
      result->add(i + j, n * N, d * D);
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
  while (!coefficients.empty() && coefficients[coefficients.size() - 2] == 0) {
    coefficients.pop_back();
    coefficients.pop_back();
  }
}
