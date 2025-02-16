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
    numerator = n / std::gcd(n, d);
    denominator = d / std::gcd(n, d);
}

std::string Fraction::toString() {
    if (denominator == 1) {
      return std::to_string(numerator);
    }
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

std::unique_ptr<Fraction> Fraction::add(Fraction* f) {
    return std::make_unique<Fraction>(
      numerator * f->denominator + f->numerator * denominator,
      denominator * f->denominator);
}

std::unique_ptr<Fraction> Fraction::mult(Fraction* f) {
    return std::make_unique<Fraction>(
      numerator * f->numerator,
      denominator * f->denominator);
}

bool Fraction::isOne() {
  return numerator == denominator;
}
