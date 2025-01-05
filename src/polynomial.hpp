#pragma once

#include <iostream>
#include <string>

class Polynomial {
public:
  virtual void print_polynomial(char x) = 0;
  virtual ~Polynomial() {}
};

class Poly final : public Polynomial {
public:
  std::vector<int> coefficients;
  void print_polynomial(char x) override;
  Poly() {
    coefficients.reserve(16);
  }
};
