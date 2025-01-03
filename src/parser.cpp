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

ListEx Parser::parse(std::istream* in, bool is_nested) {
  Parser::consume_whitespace(in);
  ListEx result{};
  char c;
  while ((c = in->peek()) != -1) {
    if (std::isdigit(c)) {
      NumEx ex = readNumber(in);
      result.add(ex);
      Parser::consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in->get();
        ListEx ex = parse(in, true);
        result.add(ex);
        break;
      }
      case ')': {
        in->get();
        if (!is_nested) {
          throw std::runtime_error("unmatched closing");
        }
        Parser::consume_whitespace(in);
        return result;
      }
      case '+': {
        in->get();
        PlusEx ex{};
        result.add(ex);
        break;
      }
      case '-': {
        in->get();
        MinusEx ex{};
        result.add(ex);
        break;
      }
      case '*': {
        in->get();
        MultEx ex{};
        result.add(ex);
        break;
      }
      default:
        throw std::runtime_error(std::string("VarExp? <") + c + '>');
    }
    Parser::consume_whitespace(in);
  }
  if (is_nested) {
    throw std::runtime_error("unmatched opening");
  }
  return result;
}

ListEx Parser::parse(std::istream* in) {
  consume_whitespace(in);
  char c = in->peek();
  if (c == '(') {
    in->get();
  }
  return parse(in, c == '(');
}
