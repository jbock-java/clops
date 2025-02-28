#include <numeric>
#include <stdexcept>

#include "fraction.hpp"

Fraction::Fraction(int n) {
  numerator = n;
  denominator = 1;
}

Fraction::Fraction(int n, int d) {
  if (d == 0) {
    throw std::runtime_error("denumerator cannot be zero");
  }
  int gd = std::gcd(n, d);
  numerator = n / gd;
  denominator = d / gd;
}

std::string Fraction::toString() const {
  if (denominator == 1) {
    return std::to_string(numerator);
  }
  return std::to_string(numerator) + "/" + std::to_string(denominator);
}

std::unique_ptr<Fraction> Fraction::add(int n, int d) const {
  return std::make_unique<Fraction>(numerator * d + denominator * n, denominator * d);
}

std::unique_ptr<Fraction> Fraction::mult(Fraction* f) {
    return std::make_unique<Fraction>(
      numerator * f->numerator,
      denominator * f->denominator);
}

bool Fraction::isOne() const {
  return numerator == denominator;
}

bool Fraction::isZero() const {
  return numerator == 0;
}
