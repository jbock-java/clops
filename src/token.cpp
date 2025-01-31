#include <stdexcept>
#include <vector>
#include <memory>

#include "token.hpp"

std::unique_ptr<Polynomial> ListToken::eval() {
  if (value.size() == 1) {
    return value[0]->eval();
  }
  throw std::runtime_error("not implemented");
}

std::unique_ptr<HeadEx> ListToken::transform() {
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
