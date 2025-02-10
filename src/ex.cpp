#include <vector>
#include <memory>
#include <sstream>

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

std::string symbolToString(Symbol symbol) {
  switch (symbol) {
    case Symbol::PLUS: return "+";
    case Symbol::MULT: return "*";
  }
  return "UNKNOWN_SYMBOL";
}

std::string HeadEx::toString() {
  if (value.empty()) {
    return "(" + symbolToString(head) + ")";
  }
  std::stringstream sb;
  for (size_t i = 0; i < value.size(); i++) {
    if (i != 0) {
      sb << " ";
    }
    sb << value[i]->toString();
  }
  return "(" + symbolToString(head) + " " + sb.str() + ")";
}

std::string VarEx::toString() {
  return "x^" + std::to_string(degree);
}

std::string NumEx::toString() {
  return std::to_string(value);
}

std::string NilEx::toString() {
  return "NIL";
}
