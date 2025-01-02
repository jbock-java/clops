#include <stdexcept>
#include <vector>
#include <memory>
#include "ex.hpp"


void ListEx::add(NumEx ex) {
  value.push_back(std::make_shared<NumEx>(ex));
}

void ListEx::add(VarEx ex) {
  value.push_back(std::make_shared<VarEx>(ex));
}

void ListEx::add(PlusEx ex) {
  value.push_back(std::make_shared<PlusEx>(ex));
}

void ListEx::add(MinusEx ex) {
  value.push_back(std::make_shared<MinusEx>(ex));
}

void ListEx::add(MultEx ex) {
  value.push_back(std::make_shared<MultEx>(ex));
}

void ListEx::add(ListEx ex) {
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
  return Polynomial(degree);
}

Polynomial NumEx::eval() {
  return Polynomial(value);
}
