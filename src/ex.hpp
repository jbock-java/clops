#pragma once

#include <vector>
#include <memory>

#include "polynomial.hpp"

class Ex {

public:
  virtual Polynomial eval() = 0;
  virtual ~Ex() {}
};

class NumEx final: public Ex {
public:
  const int value;
  NumEx(int value)
    : value(value)
  {}
  Polynomial eval() override;
};

class VarEx final: public Ex {
public:
  const char* var;
  const int degree;
  VarEx(char* var, int degree)
    : var(var)
    , degree(degree)
  {}
  Polynomial eval() override;
};

class PlusEx final: public Ex {
public:
  Polynomial eval() override;
};

class MinusEx final: public Ex {
public:
  Polynomial eval() override;
};

class MultEx final: public Ex {
public:
  Polynomial eval() override;
};

class ListEx final: public Ex {
public:
  Polynomial eval() override;
  void addNumEx(int number);
  void add(VarEx ex);
  void addPlusEx();
  void addMinusEx();
  void addMultEx();
  void add(ListEx ex);
  ListEx() {
    value.reserve(16);
  }
private:
  std::vector<std::shared_ptr<Ex>> value;
};
