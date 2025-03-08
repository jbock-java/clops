#include <vector>
#include <memory>
#include <sstream>

#include "ex.hpp"

std::unique_ptr<Polynomial> HeadEx::evalPlus() {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(16);
  for (size_t i = 0; i < value.size(); i++) {
    result->mutAdd(value[i]->eval().get());
  }
  return result;
}

std::unique_ptr<Polynomial> HeadEx::evalMult() {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(16);
  result->set(0, 1, 1);
  for (size_t i = 0; i < value.size(); i++) {
    result = result->mult(value[i]->eval().get()); // TODO more efficient
  }
  return result;
}

std::unique_ptr<Polynomial> HeadEx::evalDiv() {
  throw std::runtime_error(toString() + ": div not implemented");
}

std::unique_ptr<Polynomial> HeadEx::eval() {
  switch (head) {
    case Symbol::PLUS: return evalPlus();
    case Symbol::MULT: return evalMult();
    case Symbol::DIV: return evalDiv();
  }
  throw std::runtime_error("unknown symbol");
}

void HeadEx::add(std::unique_ptr<Ex> ex) {
  if (ex->isNil()) {
    return;
  }
  value.push_back(std::move(ex));
}

std::unique_ptr<Polynomial> VarEx::eval() {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(degree);
  result->set(degree, 1, 1);
  return result;
}

std::unique_ptr<Polynomial> NumEx::eval() {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(0);
  result->set(0, value.numerator, value.denominator);
  return result;
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
    case Symbol::DIV: return "/";
  }
  return "UNKNOWN_SYMBOL";
}

std::string HeadEx::toString() const {
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

std::string VarEx::toString() const {
  return "x^" + std::to_string(degree);
}

std::string NumEx::toString() const {
  return value.toString();
}

std::string NilEx::toString() const {
  return "NIL";
}
