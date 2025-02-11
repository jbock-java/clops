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
    std::shared_ptr<Ex> transformed = token->transform();
    if ((b & B_STRONG) != 0) {
      if ((b & B_MINUSBOUND) != 0) {
        HeadEx neg(Symbol::MULT, 2);
        NumEx minusOne(-1);
        neg.add(std::make_shared<NumEx>(minusOne));
        neg.add(transformed);
        region.add(std::make_shared<HeadEx>(neg));
      } else {
        region.add(transformed);
      }
      if ((b & B_END) != 0) {
        HeadEx regionCopy = region;
        std::shared_ptr<Ex> unwrapped = unwrap(regionCopy);
        exprsCopy.add(unwrapped);
      }
    } else {
      exprsCopy.add(transformed);
    }
  }
  if (exprsCopy.value.empty()) {
    return unwrap(region);
  }
  if (!region.value.empty()) {
    exprsCopy.add(unwrap(region));
  }
  return std::make_shared<HeadEx>(exprsCopy);
}

std::shared_ptr<Ex> PlusToken::transform() {
  NilEx result;
  return std::make_shared<NilEx>(result);
}

std::shared_ptr<Ex> MinusToken::transform() {
  NilEx result;
  return std::make_shared<NilEx>(result);
}

std::shared_ptr<Ex> MultToken::transform() {
  NilEx result;
  return std::make_shared<NilEx>(result);
}

std::shared_ptr<Ex> VarToken::transform() {
  VarEx result(degree);
  return std::make_unique<VarEx>(result);
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
