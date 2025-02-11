#pragma once

#include <vector>
#include <memory>
#include <string>

#include "polynomial.hpp"

class Ex {

public:
  virtual bool isNil() = 0;
  virtual std::unique_ptr<Polynomial> eval() = 0;
  virtual std::string toString() = 0;
  virtual ~Ex() {}
};

class NumEx final: public Ex {
  const int value;
public:
  NumEx(int value)
    : value(value)
  {}
  std::unique_ptr<Polynomial> eval() override;
  std::string toString() override;
  bool isNil() override;
};

class VarEx final: public Ex {
  const size_t degree;
public:
  VarEx(size_t degree)
    : degree(degree)
  {}
  std::unique_ptr<Polynomial> eval() override;
  std::string toString() override;
  bool isNil() override;
};

enum class Symbol {
  PLUS,
  MULT,
};

class NilEx final: public Ex {
public:
  NilEx() {}
  std::unique_ptr<Polynomial> eval() override;
  std::string toString() override;
  bool isNil() override;
};

class HeadEx final: public Ex {
public:
  const Symbol head;
  std::vector<std::shared_ptr<Ex>> value;
  HeadEx(Symbol head, int capacity)
    : head(head) {
    value.reserve(capacity);
  }
  std::unique_ptr<Polynomial> evalPlus();
  std::unique_ptr<Polynomial> evalMult();
  void add(std::shared_ptr<Ex> ex);
  std::unique_ptr<Polynomial> eval() override;
  std::string toString() override;
  bool isNil() override;
};
