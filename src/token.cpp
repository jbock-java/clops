#include <stdexcept>
#include <vector>
#include <memory>

#include "token.hpp"

static const int B_STRONG = 4;
static const int B_MINUSBOUND = 16;
static const int B_END = 1;

std::unique_ptr<Polynomial> ListToken::eval() {
  if (value.size() == 1) {
    return value[0]->eval();
  }
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Ex> ListToken::transform() {
  if (value.size() == 1) {
    return value[0]->transform();
  }
  throw std::runtime_error("ListToken transform, not implemented");
}

std::unique_ptr<Polynomial> PlusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Ex> PlusToken::transform() {
  throw std::runtime_error("PlusToken transform not implemented");
}

std::unique_ptr<Polynomial> MinusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Ex> MinusToken::transform() {
  throw std::runtime_error("MinusToken transform not implemented");
}

std::unique_ptr<Polynomial> MultToken::eval() {
  throw std::runtime_error("not implemented");
}

std::unique_ptr<Ex> MultToken::transform() {
  throw std::runtime_error("MultToken transform not implemented");
}

std::unique_ptr<Polynomial> VarToken::eval() {
  return std::make_unique<Vary>(degree);
}

std::unique_ptr<Ex> VarToken::transform() {
  VarEx result(degree);
  return std::make_unique<VarEx>(result);
}

std::unique_ptr<Polynomial> NumToken::eval() {
  return std::make_unique<Consty>(value);
}

std::unique_ptr<Ex> NumToken::transform() {
  NumEx result(value);
  return std::make_unique<NumEx>(result);
}
