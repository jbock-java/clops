#include <vector>
#include <memory>

#include "ex.hpp"

std::unique_ptr<Polynomial> HeadEx::evalPlus() {
  throw std::runtime_error("plus not implemented");
}

std::unique_ptr<Polynomial> HeadEx::evalMult() {
  throw std::runtime_error("mult not implemented");
}

std::unique_ptr<Polynomial> HeadEx::eval() {
  if (head == Symbol::PLUS) {
    return evalPlus();
  }
  if (head == Symbol::MULT) {
    return evalMult();
  }
  throw std::runtime_error("unknown symbol");
}

void HeadEx::add(std::shared_ptr<Ex> ex) {
  if (ex->isNil()) {
    return;
  }
  value.push_back(ex);
}

std::unique_ptr<Polynomial> VarEx::eval() {
  Vary result(degree);
  return std::make_unique<Vary>(result);
}

std::unique_ptr<Polynomial> NumEx::eval() {
  Consty result(value);
  return std::make_unique<Consty>(result);
}

std::unique_ptr<Polynomial> NilEx::eval() {
  throw std::runtime_error("NilEx eval not implemented");
}

bool HeadEx::isNil() {
  return false;
}

bool VarEx::isNil() {
  return false;
}

bool NumEx::isNil() {
  return false;
}

bool NilEx::isNil() {
  return true;
}
