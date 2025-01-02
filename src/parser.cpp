#include <cctype>
#include <stdexcept>
#include <string.h>

#include "parser.hpp"
#include "ex.hpp"

void Parser::consume_whitespace(std::istream* in) {
  char c;
  while ((c = in->peek()) != -1) {
    char c = in->peek();
    if (c == ' ') {
      in->get();
    } else if (c == '\n') {
      in->get();
    } else {
      break;
    }
  }
}

NumEx readNumber(std::istream* in) {
  char c = in->get();
  NumEx result(c - '0');
  return result;
}

ListEx Parser::parse(std::istream* in) {
  consume_whitespace(in);
  ListEx result{};
  char c;
  while ((c = in->peek()) != -1) {
    if (std::isdigit(c)) {
      NumEx ex = readNumber(in);
      result.add(ex);
      consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in->get();
        ListEx ex = parse(in);
        result.add(ex);
      }
      case ')': {
        in->get();
        return result;
      }
      case '+': {
        in->get();
        PlusEx ex{};
        result.add(ex);
      }
      case '-': {
        in->get();
        MinusEx ex{};
        result.add(ex);
      }
      case '*': {
        in->get();
        MultEx ex{};
        result.add(ex);
      }
      default:
        std::string str = "VarExp? <";
        throw std::runtime_error(str + c + '>');
    }
    consume_whitespace(in);
  }
  return result;
}
