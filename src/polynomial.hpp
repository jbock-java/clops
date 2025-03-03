#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "fraction.hpp"
#include "monomial.hpp"

class Polynomial {
public:
  std::vector<std::unique_ptr<Fraction>> coefficients;
  std::string toString(char x);
  size_t getDegree();
  std::unique_ptr<Polynomial> add(Polynomial* other);
  std::unique_ptr<Polynomial> monoMult(Fraction* coefficient, size_t degree);
  std::unique_ptr<Polynomial> mult(Polynomial* other);
  std::unique_ptr<Monomial> lead();
  Polynomial(size_t degree) {
    coefficients.reserve(degree + 1);
  }
};
