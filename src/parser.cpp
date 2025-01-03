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

int readNumber(std::istream* in) {
  int result = in->get() - '0';
  char c;
  while (true) {
    c = in->peek() - '0';
    if (c < 0 || c > 9) {
      break;
    }
    in->get();
    result = 10 * result + c;
  }
  return result;
}

ListEx Parser::parse(std::istream* in, bool is_nested) {
  Parser::consume_whitespace(in);
  ListEx result{};
  char c;
  while (true) {
    c = in->peek();
    if (c == -1) {
      break;
    }
    if (c == ';') {
      in->get();
      break;
    }
    if (std::isdigit(c)) {
      result.addNumEx(readNumber(in));
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
        result.addPlusEx();
        break;
      }
      case '-': {
        in->get();
        result.addMinusEx();
        break;
      }
      case '*': {
        in->get();
        result.addMultEx();
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
