#include <numeric>

#include "fraction.hpp"

Fraction::Fraction(int n, int d) {
    numerator = n / std::gcd(n, d);
    denominator = d / std::gcd(n, d);
}

std::string Fraction::toString() {
    return to_string(numerator) + "/" + to_string(denominator);
}

Fraction Fraction::add(Fraction f) {
    return Fraction(
      numerator * f.denominator + f.numerator * denominator,
      denominator * f.denominator);
}

Fraction Fraction::multiply(Fraction f) {
    return Fraction(
      numerator * f.numerator,
      denominator * f.denominator);
}
