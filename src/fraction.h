#pragma once

#include <string>

class Fraction {
public:
    const int numerator;
    const int denominator;
    Fraction(int numerator, int denominator);
    Fraction add(Fraction other);
    Fraction multiply(Fraction other);
    std::string toString();
};
