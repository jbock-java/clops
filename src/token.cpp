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

std::shared_ptr<Ex> unwrap(HeadEx expr) {
  if (expr.value.size() == 1) {
    return expr.value[0];
  }
  return std::make_shared<HeadEx>(expr);
}

std::shared_ptr<Ex> ListToken::transform() {
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
  for (int i = 0; i < value.size(); i++) {
    std::shared_ptr<Token> token = value[i];
    int b = bound[i];
    std::shared_ptr<Ex> transformed = token->transform();
    if ((b & B_STRONG) != 0) {
      if ((b & B_MINUSBOUND) != 0) {
        HeadEx neg(Symbol::MULT, 2);
        VarEx minusOne(-1);
        neg.value.push_back(std::make_shared<VarEx>(minusOne));
        neg.value.push_back(transformed);
        region.value.push_back(std::make_shared<HeadEx>(neg));
      } else {
        region.value.push_back(transformed);
      }
      if ((b & B_END) != 0) {
        HeadEx regionCopy = region;
        std::shared_ptr<Ex> unwrapped = unwrap(regionCopy);
        exprsCopy.value.push_back(unwrapped);
      }
    } else {
      region.value.push_back(transformed);
    }
  }
  if (exprsCopy.value.empty()) {
    return unwrap(region);
  }
  if (!region.value.empty()) {
    exprsCopy.value.push_back(unwrap(region));
  }
  return std::make_shared<HeadEx>(exprsCopy);
}

std::unique_ptr<Polynomial> PlusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::shared_ptr<Ex> PlusToken::transform() {
  throw std::runtime_error("PlusToken transform not implemented");
}

std::unique_ptr<Polynomial> MinusToken::eval() {
  throw std::runtime_error("not implemented");
}

std::shared_ptr<Ex> MinusToken::transform() {
  throw std::runtime_error("MinusToken transform not implemented");
}

std::unique_ptr<Polynomial> MultToken::eval() {
  throw std::runtime_error("not implemented");
}

std::shared_ptr<Ex> MultToken::transform() {
  throw std::runtime_error("MultToken transform not implemented");
}

std::unique_ptr<Polynomial> VarToken::eval() {
  return std::make_unique<Vary>(degree);
}

std::shared_ptr<Ex> VarToken::transform() {
  VarEx result(degree);
  return std::make_unique<VarEx>(result);
}

std::unique_ptr<Polynomial> NumToken::eval() {
  return std::make_unique<Consty>(value);
}

std::shared_ptr<Ex> NumToken::transform() {
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
