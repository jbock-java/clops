#pragma once

#include <vector>
#include <memory>
#include <string>

#include "polynomial.hpp"
#include "ex.hpp"

enum class Strength {
  STRONG, WEAK, UNDECIDED
};

class Token {

public:
  virtual std::shared_ptr<Ex> transform() = 0;
  virtual Strength leftStrength() = 0;
  virtual Strength rightStrength() = 0;
  virtual bool isMinus() = 0;
  virtual ~Token() {}
};

class NumToken final: public Token {
public:
  const int value;
  NumToken(int value)
    : value(value)
  {}
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
};

class VarToken final: public Token {
public:
  const int degree;
  VarToken(int degree)
    : degree(degree)
  {}
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
};

class PlusToken final: public Token {
public:
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
};

class MinusToken final: public Token {
public:
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
};

class MultToken final: public Token {
public:
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
};

class ListToken final: public Token {
public:
  std::vector<std::unique_ptr<Token>> value;
  std::shared_ptr<Ex> transform() override;
  Strength leftStrength() override;
  Strength rightStrength() override;
  bool isMinus() override;
  ListToken(size_t capacity) {
    value.reserve(capacity);
  }
};
