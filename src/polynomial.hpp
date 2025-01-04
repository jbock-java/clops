#pragma once

#include <iostream>
#include <string>

class Polynomial {
public:
  virtual void print_polynomial() = 0;
  virtual ~Polynomial() {}
};

class Poly final : public Polynomial {
public:
  std::string name;
  std::vector<int> coefficients;
  void print_polynomial() override;
  Poly()
    : name(std::string("x"))
  {
    coefficients.reserve(16);
  }
};
