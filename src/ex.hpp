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
public:
  const int value;
  NumEx(int value)
    : value(value)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

class VarEx final: public Ex {
public:
  const int degree;
  VarEx(int degree)
    : degree(degree)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

class PlusEx final: public Ex {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class MinusEx final: public Ex {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class MultEx final: public Ex {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class ListEx final: public Ex {
public:
  std::unique_ptr<Polynomial> eval() override;
  void addNumEx(int number);
  void addVarEx(VarEx ex);
  void addPlusEx();
  void addMinusEx();
  void addMultEx();
  void addListEx(ListEx& ex);
  ListEx() {
    value.reserve(16);
  }
private:
  std::vector<std::shared_ptr<Ex>> value;
};
