#include <stdexcept>
#include <vector>
#include <memory>
#include "token.hpp"

void ListToken::addNumToken(int number) {
  value.push_back(std::make_shared<NumToken>(NumToken(number)));
}

void ListToken::addVarToken(VarToken ex) {
  value.push_back(std::make_shared<VarToken>(ex));
}

void ListToken::addPlusToken() {
  value.push_back(std::make_shared<PlusToken>(PlusToken()));
}

void ListToken::addMinusToken() {
  value.push_back(std::make_shared<MinusToken>(MinusToken()));
}

void ListToken::addMultToken() {
  value.push_back(std::make_shared<MultToken>(MultToken()));
}

void ListToken::addListToken(ListToken& ex) {
  value.push_back(std::make_shared<ListToken>(ex));
}

std::unique_ptr<Polynomial> ListToken::eval() {
  if (value.size() == 1) {
    return value[0]->eval();
  }
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> PlusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> MinusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> MultToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> VarToken::eval() {
  return std::make_unique<Vary>(degree);
}

std::unique_ptr<Polynomial> NumToken::eval() {
  return std::make_unique<Consty>(value);
}
