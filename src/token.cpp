#include <stdexcept>
#include <vector>
#include <memory>

#include "token.hpp"

static const int B_STRONG = 4;
static const int B_MINUSBOUND = 16;
static const int B_END = 1;

bool isStrong(
  Strength leftStrength,
  Strength rightStrength) {
  if (leftStrength != Strength::UNDECIDED) {
    return leftStrength == Strength::WEAK ? false : true;
  }
  return rightStrength == Strength::WEAK ? false : true;
}

std::unique_ptr<Ex> unwrap(std::unique_ptr<HeadEx> expr) {
  if (expr->value.size() == 1) {
    return std::move(expr->value[0]);
  }
  return expr;
}

std::unique_ptr<Ex> ListToken::transform() {
  if (value.size() == 1) {
    return value[0]->transform();
  }
  std::unique_ptr<HeadEx> exprsCopy = std::make_unique<HeadEx>(Symbol::PLUS, value.size());
  std::unique_ptr<HeadEx> region = std::make_unique<HeadEx>(Symbol::MULT, value.size());
  std::vector<int> bound(value.size());
  for (size_t i = 0; i < value.size() - 1; i++) {
    if (isStrong(value[i]->leftStrength(), value[i + 1]->rightStrength())) {
      bound[i] |= B_STRONG;
      bound[i + 1] |= B_STRONG;
      if (value[i]->isMinus()) {
        bound[i + 1] |= B_MINUSBOUND;
      }
    } else if ((bound[i] & B_STRONG) != 0) {
      bound[i] |= B_END;
    }
  }
  for (size_t i = 0; i < value.size(); i++) {
    std::unique_ptr<Token> token = std::move(value[i]);
    int b = bound[i];
    if ((b & B_STRONG) != 0) {
      if ((b & B_MINUSBOUND) != 0) {
        std::unique_ptr<HeadEx> neg = std::make_unique<HeadEx>(Symbol::MULT, 2);
        neg->add(std::make_unique<NumEx>(-1));
        neg->add(token->transform());
        region->add(std::move(neg));
      } else {
        region->add(token->transform());
      }
      if ((b & B_END) != 0) {
        exprsCopy->add(unwrap(std::move(region)));
        region = std::make_unique<HeadEx>(Symbol::MULT, value.size());
      }
    } else {
      exprsCopy->add(token->transform());
    }
  }
  if (exprsCopy->value.empty()) {
    return unwrap(std::move(region));
  }
  if (!region->value.empty()) {
    exprsCopy->add(unwrap(std::move(region)));
  }
  return exprsCopy;
}

std::unique_ptr<Ex> PlusToken::transform() {
  NilEx result;
  return std::make_unique<NilEx>(result);
}

std::unique_ptr<Ex> MinusToken::transform() {
  NilEx result;
  return std::make_unique<NilEx>(result);
}

std::unique_ptr<Ex> MultToken::transform() {
  NilEx result;
  return std::make_unique<NilEx>(result);
}

std::unique_ptr<Ex> VarToken::transform() {
  VarEx result(degree);
  return std::make_unique<VarEx>(result);
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
