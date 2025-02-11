#include <vector>
#include <memory>
#include <sstream>

#include "ex.hpp"

std::unique_ptr<Polynomial> HeadEx::evalPlus() {
  Polynomial zero(16);
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(zero);
  for (size_t i = 0; i < value.size(); i++) {
    std::unique_ptr<Polynomial> p = value[i]->eval();
    result = result->add(std::move(p));
  }
  return result;
}

std::unique_ptr<Polynomial> HeadEx::evalMult() {
  Polynomial one(16);
  one.coefficients.push_back(1);
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(one);
  for (size_t i = 0; i < value.size(); i++) {
    std::unique_ptr<Polynomial> p = value[i]->eval();
    result = result->mult(std::move(p));
  }
  return result;
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
  Polynomial result(degree);
  for (size_t i = 0; i < degree; i++) {
    result.coefficients.push_back(0);
  }
  result.coefficients.push_back(1);
  return std::make_unique<Polynomial>(result);
}

std::unique_ptr<Polynomial> NumEx::eval() {
  Polynomial result(0);
  result.coefficients.push_back(value);
  return std::make_unique<Polynomial>(result);
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
