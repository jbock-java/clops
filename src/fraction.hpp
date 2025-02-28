#pragma once

#include <memory>
#include <string>

class Fraction {
public:
    int numerator;
    int denominator;
    Fraction(int numerator);
    Fraction(int numerator, int denominator);
    std::unique_ptr<Fraction> add(int n, int d) const;
    std::unique_ptr<Fraction> mult(Fraction* other);
    bool isOne() const;
    bool isZero() const;
    std::string toString() const;
};
