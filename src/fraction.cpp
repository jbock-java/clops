#include <numeric>
#include <stdexcept>

#include "fraction.hpp"

std::string Fraction::toString() const {
  if (denominator == 1) {
    return std::to_string(numerator);
  }
  return std::to_string(numerator) + "/" + std::to_string(denominator);
}

std::unique_ptr<Fraction> Fraction::add(int n, int d) const {
  return std::make_unique<Fraction>(numerator * d + denominator * n, denominator * d);
}

std::unique_ptr<Fraction> Fraction::mult(int n, int d) const {
    return std::make_unique<Fraction>(
      numerator * n,
      denominator * d);
}

bool Fraction::isOne() const {
  return numerator == denominator;
}

bool Fraction::isZero() const {
  return numerator == 0;
}
