#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "fraction.hpp"
#include "monomial.hpp"

class Polynomial {
public:
  std::vector<int> coefficients;
  std::string toString(char x) const;
  size_t getDegree() const;
  size_t size() const;
  std::unique_ptr<Polynomial> add(Polynomial* other) const;
  int getNumerator(size_t i) const;
  int getDenominator(size_t i) const;
  std::unique_ptr<Polynomial> mult(Polynomial* other) const;
  std::unique_ptr<Monomial> lead() const;
  void mutAdd(Polynomial* other);
  void set(size_t i, int numerator, int denominator);
  Polynomial(size_t degree) {
    coefficients.reserve(2 * (degree + 1));
  }
private:
  void add(size_t i, int numerator, int denominator);
  void shrink();
};
