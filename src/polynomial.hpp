#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "fraction.hpp"

class Polynomial {
public:
  std::vector<std::unique_ptr<Fraction>> coefficients;
  std::string toString(char x);
  std::unique_ptr<Fraction> getCoefficient(size_t i);
  size_t getDegree();
  std::unique_ptr<Polynomial> add(Polynomial* other);
  std::unique_ptr<Polynomial> monoMult(Fraction* coefficient, size_t degree);
  std::unique_ptr<Polynomial> mult(Polynomial* other);
  Polynomial(size_t degree) {
    coefficients.reserve(degree + 1);
  }
};
