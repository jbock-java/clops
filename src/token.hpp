#pragma once

#include <vector>
#include <memory>
#include <string>

#include "ex.hpp"

enum class Strength {
  STRONG, WEAK, UNDECIDED
};

class Token {

public:
  virtual std::unique_ptr<Ex> transform() const = 0;
  virtual Strength leftStrength() const = 0;
  virtual Strength rightStrength() const = 0;
  virtual bool isMinus() const = 0;
  virtual bool isDiv() const = 0;
  virtual ~Token() {}
};

class NumToken final: public Token {
public:
  const int value;
  NumToken(int value)
    : value(value)
  {}
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class VarToken final: public Token {
public:
  const int degree;
  VarToken(int degree)
    : degree(degree)
  {}
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class PlusToken final: public Token {
public:
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class MinusToken final: public Token {
public:
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class MultToken final: public Token {
public:
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class DivToken final: public Token {
public:
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
};

class ListToken final: public Token {
public:
  std::vector<std::unique_ptr<Token>> value;
  std::unique_ptr<Ex> transform() const override;
  Strength leftStrength() const override;
  Strength rightStrength() const override;
  bool isMinus() const override;
  bool isDiv() const override;
  ListToken(size_t capacity) {
    value.reserve(capacity);
  }
};
