#include "ex.hpp"

class NumEx final: public Ex {

public:
  const int value;
  NumEx(int value)
    : value(value)
  {}
  Polynomial eval() override {
    return Polynomial(value);
  }
};
