#pragma once

#include "fraction.hpp"

class Monomial {
public:
  const Fraction coefficient;
  const size_t degree;
  Monomial(Fraction coefficient, size_t degree) :
    coefficient(coefficient),
    degree(degree)
  {}
};
