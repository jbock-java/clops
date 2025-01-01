#include "ex.hpp"

class NumEx: public Ex {

public:
  const int value;
  NumEx(int value)
    : value(value)
  {}
  Polynomial eval() {
    return Polynomial(value);
  }
};
