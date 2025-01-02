#include <stdexcept>
#include <vector>
#include <memory>
#include "ex.hpp"

class NumEx final: public Ex {
public:
  const int value;
  NumEx(int value)
    : value(value)
  {}
  Polynomial eval() override;
};

class VarEx final: public Ex {
public:
  const char* var;
  const int degree;
  VarEx(char* var, int degree)
    : var(var)
    , degree(degree)
  {}
  Polynomial eval() override;
};

class PlusEx final: public Ex {
public:
  Polynomial eval() override;
};

class MinusEx final: public Ex {
public:
  Polynomial eval() override;
};

class MultEx final: public Ex {
public:
  Polynomial eval() override;
};

class ListEx final: public Ex {
public:
  Polynomial eval() override;
  void add(NumEx ex);
  void add(VarEx ex);
  void add(PlusEx ex);
  void add(MinusEx ex);
  void add(MultEx ex);
  void add(ListEx ex);
private:
  std::vector<std::shared_ptr<Ex>> value;
};

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
