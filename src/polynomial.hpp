#pragma once

#include <string>

class Polynomial {
public:
  const std::string name;
  const int value;
  Polynomial(std::string name, int value)
    : name(name)
    , value(value)
    {}
};
