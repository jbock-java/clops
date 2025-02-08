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
  HeadEx exprsCopy(Symbol::PLUS, value.size());
  HeadEx region(Symbol::MULT, value.size());
  std::vector<int> bound(value.size());
  for (int i = 0; i < value.size() - 1; i++) {
    std::shared_ptr<Token> left = value[i];
    std::shared_ptr<Token> right = value[i + 1];
  }
  throw std::runtime_error("ListToken transform, not implemented");
}

bool is_strong(
  std::shared_ptr<Token> left,
  std::shared_ptr<Token> right) {
    throw std::runtime_error("is_strong, not implemented");
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
