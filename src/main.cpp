#include <iostream>
#include <vector>
#include <memory>

#include "parser.cpp"
#include "ex.cpp"

static void print_polynomial(Polynomial& p) {
  std::cout << p.name << ' ';
  std::cout << p.value << '\n';
}

int main(int argc, const char* argv[]) {
  ListEx result;
  Parser::parse(result, std::cin);
  Polynomial p = result.eval();
  print_polynomial(p);
  return 0;
}
