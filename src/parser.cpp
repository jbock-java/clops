#include <cctype>
#include <stdexcept>
#include <string>

#include "parser.hpp"
#include "ex.hpp"

void consume_whitespace(std::istream& in) {
  char c;
  while ((c = in.peek()) != -1) {
    char c = in.peek();
    if (c == ' ') {
      in.get();
    } else if (c == '\n') {
      in.get();
    } else {
      break;
    }
  }
}

int read_number(std::istream& in) {
  int result = in.get() - '0';
  char c;
  while (true) {
    c = in.peek();
    if (!isdigit(c)) {
      break;
    }
    in.get();
    result = 10 * result + (c - '0');
  }
  return result;
}

VarEx read_var_ex(std::istream& in) {
  std::string name{};
  char c;
  while (true) {
    c = in.peek();
    if (!isdigit(c) && !isalpha(c) && c != '_') {
      break;
    }
    in.get();
    name += c;
  }
  if (c == '^') {
    in.get();
    return VarEx(name, read_number(in));
  }
  return VarEx(name, 1);
}

void parse_internal(ListEx& result, std::istream& in, bool is_nested) {
  consume_whitespace(in);
  char c;
  while (true) {
    c = in.peek();
    if (c == -1) {
      break;
    }
    if (c == ';') {
      in.get();
      break;
    }
    if (std::isdigit(c)) {
      result.addNumEx(read_number(in));
      consume_whitespace(in);
      continue;
    }
    if (c == '_' || std::isalpha(c)) {
      result.addVarEx(read_var_ex(in));
      consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in.get();
        ListEx nested;
        parse_internal(nested, in, true);
        result.addListEx(nested);
        break;
      }
      case ')':
        in.get();
        if (!is_nested) {
          throw std::runtime_error("unmatched closing");
        }
        consume_whitespace(in);
        return;
      case '+':
        in.get();
        result.addPlusEx();
        break;
      case '-':
        in.get();
        result.addMinusEx();
        break;
      case '*':
        in.get();
        result.addMultEx();
        break;
      default:
        throw std::runtime_error(std::string("Unknown character: <") + c + '>');
    }
    consume_whitespace(in);
  }
  if (is_nested) {
    throw std::runtime_error("unmatched opening");
  }
}

void Parser::parse(ListEx& result, std::istream& in) {
  consume_whitespace(in);
  char c = in.peek();
  if (c == '(') {
    in.get();
  }
  parse_internal(result, in, c == '(');
}
