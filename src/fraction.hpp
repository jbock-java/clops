#pragma once

#include <memory>
#include <string>

class Fraction {
public:
    int numerator;
    int denominator;
    Fraction(int numerator);
    Fraction(int numerator, int denominator);
    std::unique_ptr<Fraction> add(Fraction* other);
    std::unique_ptr<Fraction> mult(Fraction* other);
    bool isOne();
    bool isZero();
    std::string toString();
};
