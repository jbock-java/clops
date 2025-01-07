#pragma once

#include <vector>
#include <memory>
#include <string>

#include "polynomial.hpp"

class Token {

public:
  virtual std::unique_ptr<Polynomial> eval() = 0;
  virtual ~Token() {}
};

class NumToken final: public Token {
public:
  const int value;
  NumToken(int value)
    : value(value)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

class VarToken final: public Token {
public:
  const int degree;
  VarToken(int degree)
    : degree(degree)
  {}
  std::unique_ptr<Polynomial> eval() override;
};

class PlusToken final: public Token {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class MinusToken final: public Token {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class MultToken final: public Token {
public:
  std::unique_ptr<Polynomial> eval() override;
};

class ListToken final: public Token {
public:
  std::unique_ptr<Polynomial> eval() override;
  void addNumToken(int number);
  void addVarToken(VarToken ex);
  void addPlusToken();
  void addMinusToken();
  void addMultToken();
  void addListToken(ListToken& ex);
  ListToken() {
    value.reserve(16);
  }
private:
  std::vector<std::shared_ptr<Token>> value;
};
