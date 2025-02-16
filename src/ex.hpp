#pragma once

#include <vector>
#include <memory>
#include <string>

#include "polynomial.hpp"
#include "fraction.hpp"

class Ex {

public:
  virtual bool isNil() = 0;
  virtual std::unique_ptr<Polynomial> eval() = 0;
  virtual const std::string toString() = 0;
  virtual ~Ex() {}
};

class NumEx final: public Ex {
  Fraction value;
public:
  NumEx(Fraction value) : value(value) {};
  std::unique_ptr<Polynomial> eval() override;
  const std::string toString() override;
  bool isNil() override;
};

class VarEx final: public Ex {
  const size_t degree;
public:
  VarEx(size_t degree)
    : degree(degree)
  {}
  std::unique_ptr<Polynomial> eval() override;
  const std::string toString() override;
  bool isNil() override;
};

enum class Symbol {
  PLUS,
  MULT,
  DIV,
};

class NilEx final: public Ex {
public:
  NilEx() {}
  std::unique_ptr<Polynomial> eval() override;
  const std::string toString() override;
  bool isNil() override;
};

class HeadEx final: public Ex {
public:
  Symbol head;
  std::vector<std::unique_ptr<Ex>> value;
  HeadEx(size_t capacity) {
    value.reserve(capacity);
    head = Symbol::PLUS;
  }
  std::unique_ptr<Polynomial> evalPlus();
  std::unique_ptr<Polynomial> evalMult();
  std::unique_ptr<Polynomial> evalDiv();
  void add(std::unique_ptr<Ex> ex);
  std::unique_ptr<Polynomial> eval() override;
  const std::string toString() override;
  bool isNil() override;
};
