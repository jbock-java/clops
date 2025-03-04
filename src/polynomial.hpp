#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "fraction.hpp"
#include "monomial.hpp"

class Polynomial {
public:
  std::vector<std::unique_ptr<Fraction>> coefficients;
  std::string toString(char x) const;
  size_t getDegree() const;
  std::unique_ptr<Polynomial> add(Polynomial* other) const;
  std::unique_ptr<Polynomial> monoMult(Fraction* coefficient, size_t degree) const;
  std::unique_ptr<Polynomial> mult(Polynomial* other) const;
  std::unique_ptr<Monomial> lead() const;
  Polynomial(size_t degree) {
    coefficients.reserve(degree + 1);
  }
};
