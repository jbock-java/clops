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

bool isStrong(
  std::shared_ptr<Token> left,
  std::shared_ptr<Token> right) {
  Strength l = left->leftStrength();
  if (l != Strength::UNDECIDED) {
    return l == Strength::WEAK ? false : true;
  }
  Strength r = right->rightStrength();
  return r == Strength::WEAK ? false : true;
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
    if (isStrong(left, right)) {
      bound[i] |= B_STRONG;
      bound[i + 1] |= B_STRONG;
      if (left->isMinus()) {
        bound[i + 1] |= B_MINUSBOUND;
      }
    } else if ((bound[i] & B_STRONG) != 0) {
      bound[i] |= B_END;
    }
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

Strength ListToken::leftStrength() {
  return Strength::UNDECIDED;
}

Strength ListToken::rightStrength() {
  return Strength::UNDECIDED;
}

Strength PlusToken::leftStrength() {
  return Strength::WEAK;
}

Strength PlusToken::rightStrength() {
  return Strength::WEAK;
}

Strength MinusToken::leftStrength() {
  return Strength::STRONG;
}

Strength MinusToken::rightStrength() {
  return Strength::WEAK;
}

Strength MultToken::leftStrength() {
  return Strength::STRONG;
}

Strength MultToken::rightStrength() {
  return Strength::STRONG;
}

Strength VarToken::leftStrength() {
  return Strength::UNDECIDED;
}

Strength VarToken::rightStrength() {
  return Strength::UNDECIDED;
}

Strength NumToken::leftStrength() {
  return Strength::UNDECIDED;
}

Strength NumToken::rightStrength() {
  return Strength::UNDECIDED;
}

bool ListToken::isMinus() {
  return false;
}

bool PlusToken::isMinus() {
  return false;
}

bool MinusToken::isMinus() {
  return true;
}

bool MultToken::isMinus() {
  return false;
}

bool VarToken::isMinus() {
  return false;
}

bool NumToken::isMinus() {
  return false;
}
