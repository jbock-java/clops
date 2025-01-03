#include <stdexcept>
#include <vector>
#include <memory>
#include "ex.hpp"

void ListEx::addNumEx(int number) {
  value.push_back(std::make_shared<NumEx>(NumEx(number)));
}

void ListEx::addVarEx(VarEx ex) {
  value.push_back(std::make_shared<VarEx>(ex));
}

void ListEx::addPlusEx() {
  value.push_back(std::make_shared<PlusEx>(PlusEx()));
}

void ListEx::addMinusEx() {
  value.push_back(std::make_shared<MinusEx>(MinusEx()));
}

void ListEx::addMultEx() {
  value.push_back(std::make_shared<MultEx>(MultEx()));
}

void ListEx::addListEx(ListEx ex) {
  value.push_back(std::make_shared<ListEx>(ex));
}

Polynomial ListEx::eval() {
  if (value.size() == 1) {
    return value[0]->eval();
  }
  throw std::runtime_error("not implemented");
}

Polynomial PlusEx::eval() {
  throw std::runtime_error("not implemented");
}

Polynomial MinusEx::eval() {
  throw std::runtime_error("not implemented");
}

Polynomial MultEx::eval() {
  throw std::runtime_error("not implemented");
}

Polynomial VarEx::eval() {
  return Polynomial(name, degree);
}

Polynomial NumEx::eval() {
  return Polynomial(std::string("x"), value);
}
