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

std::shared_ptr<ListToken> parse_internal(char x, std::istream& in, bool is_nested) {
  std::vector<std::shared_ptr<Token>> result;
  result.reserve(16);
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
      result.emplace_back(std::make_shared<NumToken>(read_num(in)));
      consume_whitespace(in);
      continue;
    }
    if (std::isalpha(c)) {
      result.emplace_back(std::make_shared<VarToken>(read_var(x, in)));
      consume_whitespace(in);
      continue;
    }
    switch (c) {
      case '(': {
        in.get();
        std::shared_ptr<ListToken> nested = parse_internal(x, in, true);
        result.push_back(nested);
        break;
      }
      case ')':
        in.get();
        if (!is_nested) {
          throw std::runtime_error("unmatched closing");
        }
        consume_whitespace(in);
        return std::make_shared<ListToken>(ListToken(result));
      case '+':
        in.get();
        result.emplace_back(std::make_shared<PlusToken>());
        break;
      case '-':
        in.get();
        result.emplace_back(std::make_shared<MinusToken>());
        break;
      case '*':
        in.get();
        result.emplace_back(std::make_shared<MultToken>());
        break;
      default:
        throw std::runtime_error(std::string("Unknown character: <") + c + '>');
    }
    consume_whitespace(in);
  }
  if (is_nested) {
    throw std::runtime_error("unmatched opening");
  }
  return std::make_shared<ListToken>(ListToken(result));
}

std::shared_ptr<ListToken> Parser::parse(char x, std::istream& in) {
  consume_whitespace(in);
  char c = in.peek();
  if (c == '(') {
    in.get();
  }
  return parse_internal(x, in, c == '(');
}
