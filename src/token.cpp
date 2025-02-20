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

std::unique_ptr<Ex> ListToken::transform() const {
  if (value.size() == 1) {
    return value[0]->transform();
  }
  std::unique_ptr<HeadEx> exprsCopy = std::make_unique<HeadEx>(value.size());
  std::unique_ptr<HeadEx> region = std::make_unique<HeadEx>(value.size());
  exprsCopy->head = Symbol::PLUS;
  region->head = Symbol::MULT;
  std::vector<int> bound(value.size());
  for (size_t i = 0; i < value.size() - 1; i++) {
    if (isStrong(value[i]->leftStrength(), value[i + 1]->rightStrength())) {
      bound[i] |= B_STRONG;
      bound[i + 1] |= B_STRONG;
      if (value[i]->isMinus()) {
        bound[i + 1] |= B_MINUSBOUND;
      } else if (value[i]->isDiv()) {
        region->head = Symbol::DIV;
      }
    } else if ((bound[i] & B_STRONG) != 0) {
      bound[i] |= B_END;
    }
  }
  for (size_t i = 0; i < value.size(); i++) {
    Token* token = value[i].get();
    int b = bound[i];
    if ((b & B_STRONG) != 0) {
      if ((b & B_MINUSBOUND) != 0) {
        std::unique_ptr<HeadEx> neg = std::make_unique<HeadEx>(2);
        neg->head = Symbol::MULT;
        neg->add(std::make_unique<NumEx>(-1));
        neg->add(token->transform());
        region->add(std::move(neg));
      } else {
        region->add(token->transform());
      }
      if ((b & B_END) != 0) {
        exprsCopy->add(unwrap(std::move(region)));
        region = std::make_unique<HeadEx>(value.size());
        region->head = Symbol::MULT;
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

std::unique_ptr<Ex> PlusToken::transform() const {
  return std::make_unique<NilEx>();
}

std::unique_ptr<Ex> MinusToken::transform() const {
  return std::make_unique<NilEx>();
}

std::unique_ptr<Ex> MultToken::transform() const {
  return std::make_unique<NilEx>();
}

std::unique_ptr<Ex> DivToken::transform() const {
  return std::make_unique<NilEx>();
}

std::unique_ptr<Ex> VarToken::transform() const {
  return std::make_unique<VarEx>(degree);
}

std::unique_ptr<Ex> NumToken::transform() const {
  return std::make_unique<NumEx>(value);
}

Strength ListToken::leftStrength() const {
  return Strength::UNDECIDED;
}

Strength ListToken::rightStrength() const {
  return Strength::UNDECIDED;
}

Strength PlusToken::leftStrength() const {
  return Strength::WEAK;
}

Strength PlusToken::rightStrength() const {
  return Strength::WEAK;
}

Strength MinusToken::leftStrength() const {
  return Strength::STRONG;
}

Strength MinusToken::rightStrength() const {
  return Strength::WEAK;
}

Strength MultToken::leftStrength() const {
  return Strength::STRONG;
}

Strength MultToken::rightStrength() const {
  return Strength::STRONG;
}

Strength DivToken::leftStrength() const {
  return Strength::STRONG;
}

Strength DivToken::rightStrength() const {
  return Strength::STRONG;
}

Strength VarToken::leftStrength() const {
  return Strength::UNDECIDED;
}

Strength VarToken::rightStrength() const {
  return Strength::UNDECIDED;
}

Strength NumToken::leftStrength() const {
  return Strength::UNDECIDED;
}

Strength NumToken::rightStrength() const {
  return Strength::UNDECIDED;
}

bool ListToken::isMinus() const {
  return false;
}

bool PlusToken::isMinus() const {
  return false;
}

bool MinusToken::isMinus() const {
  return true;
}

bool MultToken::isMinus() const {
  return false;
}

bool DivToken::isMinus() const {
  return false;
}

bool VarToken::isMinus() const {
  return false;
}

bool NumToken::isMinus() const {
  return false;
}

bool VarToken::isDiv() const {
  return false;
}

bool NumToken::isDiv() const {
  return false;
}

bool ListToken::isDiv() const {
  return false;
}

bool PlusToken::isDiv() const {
  return false;
}

bool MinusToken::isDiv() const {
  return false;
}

bool MultToken::isDiv() const {
  return false;
}

bool DivToken::isDiv() const {
  return true;
}
