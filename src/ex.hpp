#pragma once

#include "polynomial.hpp"

class Ex {

public:
  virtual Polynomial eval() = 0;
  virtual ~Ex() {}
};
