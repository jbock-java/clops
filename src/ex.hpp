#pragma once

#include <vector>
#include <memory>
#include <string>

#include "polynomial.hpp"

class Ex {

public:
  virtual std::unique_ptr<Polynomial> eval() = 0;
  virtual ~Ex() {}
};

class NumEx final: public Ex {
  const int value;
public:
  NumEx(int value)
    : value(value)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

class VarEx final: public Ex {
  const int degree;
public:
  VarEx(int degree)
    : degree(degree)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

enum Symbol {
  PLUS,
  MULT,
};

class HeadEx final: public Ex {
public:
  const Symbol head;
  std::unique_ptr<Polynomial> eval() override;
  HeadEx(Symbol head, int capacity)
    : head(head) {
    value.reserve(capacity);
  }
private:
  std::vector<std::shared_ptr<Ex>> value;
};
