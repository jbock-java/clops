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
  void add(NumEx ex);
  void add(VarEx ex);
  void add(PlusEx ex);
  void add(MinusEx ex);
  void add(MultEx ex);
  void add(ListEx ex);
private:
  std::vector<std::shared_ptr<Ex>> value;
};
