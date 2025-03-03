#pragma once

#include <numeric>
#include <memory>
#include <string>

class Fraction {
public:
    const int numerator;
    const int denominator;
    Fraction(int numerator) : numerator(numerator), denominator(1) {};
    Fraction(int numerator, int denominator) :
      numerator(numerator / std::gcd(numerator, denominator)),
      denominator(denominator / std::gcd(numerator, denominator))
    {};
    std::unique_ptr<Fraction> add(int n, int d) const;
    std::unique_ptr<Fraction> mult(int n, int d) const;
    std::unique_ptr<Fraction> div(int n, int d) const;
    bool isOne() const;
    bool isZero() const;
    std::string toString() const;
};
