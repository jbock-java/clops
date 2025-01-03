#pragma once

#include <vector>
#include <memory>
#include <string>

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
  const std::string name;
  const int degree;
  VarEx(std::string name, int degree)
    : name(name)
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
  void addVarEx(VarEx ex);
  void addPlusEx();
  void addMinusEx();
  void addMultEx();
  void addListEx(ListEx& ex);
private:
  std::vector<std::shared_ptr<Ex>> value;
};
