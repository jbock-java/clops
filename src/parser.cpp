#include <cctype>
#include <stdexcept>
#include <string>
#include <sstream>

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

int read_num(std::istream& in) {
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

int read_var(char x, std::istream& in) {
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
    return read_num(in);
  }
  return 1;
}

std::unique_ptr<ListToken> parse_internal(char x, std::istream& in) {
  std::unique_ptr<ListToken> result = std::make_unique<ListToken>(16);
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
      result->value.emplace_back(std::make_unique<NumToken>(read_num(in)));
      consume_whitespace(in);
      continue;
    }
    if (std::isalpha(c)) {
      result->value.emplace_back(std::make_unique<VarToken>(read_var(x, in)));
      consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in.get();
        result->value.push_back(parse_internal(x, in));
        break;
      }
      case ')':
        in.get();
        consume_whitespace(in);
        return result;
      case '+':
        in.get();
        result->value.emplace_back(std::make_unique<PlusToken>());
        break;
      case '-':
        in.get();
        result->value.emplace_back(std::make_unique<MinusToken>());
        break;
      case '*':
        in.get();
        result->value.emplace_back(std::make_unique<MultToken>());
        break;
      case '/':
        in.get();
        result->value.emplace_back(std::make_unique<DivToken>());
        break;
      default:
        throw std::runtime_error(std::string("Unknown character: <") + c + '>');
    }
    consume_whitespace(in);
  }
  return result;
}

std::unique_ptr<ListToken> Parser::parse(char x, std::istream& in) {
  std::ostringstream buf;
  while (true) {
    char c = in.get();
    if (c == -1) {
      break;
    }
    buf << c;
  }
  std::stringstream ss(buf.str());
  return parse_internal(x, ss);
}
