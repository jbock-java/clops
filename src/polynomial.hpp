#pragma once

#include <iostream>
#include <string>

class Polynomial {
public:
  std::string name;
  std::vector<int> coefficients;
  void print_polynomial();
  Polynomial()
    : name(std::string("x"))
  {
    coefficients.reserve(16);
  }
};
