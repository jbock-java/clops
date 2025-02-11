#pragma once

#include <iostream>
#include <string>

class Polynomial {
public:
  std::vector<int> coefficients;
  std::string toString(char x);
  int getCoefficient(size_t i);
  size_t getDegree();
  std::unique_ptr<Polynomial> add(std::unique_ptr<Polynomial> other);
  std::unique_ptr<Polynomial> monoMult(int coefficient, size_t degree);
  std::unique_ptr<Polynomial> mult(std::unique_ptr<Polynomial> other);
  Polynomial(size_t degree) {
    coefficients.reserve(degree + 1);
  }
};
