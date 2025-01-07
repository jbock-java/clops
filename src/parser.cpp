#include <cctype>
#include <stdexcept>
#include <string>

#include "parser.hpp"
#include "token.hpp"

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

VarToken read_var_token(char x, std::istream& in) {
  char c = in.get();
  if (c != x) {
    throw std::runtime_error(std::string("unknown char: ") + c);
  }
  c = in.peek();
  if (c == '^') {
    in.get();
    if (!isdigit(in.peek())) {
      throw std::runtime_error(std::string("expecting number after ^ but found ") + c);
    }
    return VarToken(read_number(in));
  }
  return VarToken(1);
}

void parse_internal(char x, ListToken& result, std::istream& in, bool is_nested) {
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
      result.addNumToken(read_number(in));
      consume_whitespace(in);
      continue;
    }
    if (std::isalpha(c)) {
      result.addVarToken(read_var_token(x, in));
      consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in.get();
        ListToken nested;
        parse_internal(x, nested, in, true);
        result.addListToken(nested);
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
        result.addPlusToken();
        break;
      case '-':
        in.get();
        result.addMinusToken();
        break;
      case '*':
        in.get();
        result.addMultToken();
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

void Parser::parse(char x, ListToken& result, std::istream& in) {
  consume_whitespace(in);
  char c = in.peek();
  if (c == '(') {
    in.get();
  }
  parse_internal(x, result, in, c == '(');
}
