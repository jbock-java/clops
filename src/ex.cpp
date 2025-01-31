#include <vector>
#include <memory>

#include "ex.hpp"

std::unique_ptr<Polynomial> HeadEx::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> VarEx::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Polynomial> NumEx::eval() {
  throw std::runtime_error("not implemented");
}
