#include <iostream>
#include <vector>

#include "parser.cpp"
#include "ex.cpp"

static void print_polynomial(Polynomial p) {
  std::cout << p.name << ' ';
  std::cout << p.value << '\n';
}

int main(int argc, const char* argv[]) {
  ListEx list = Parser::parse(&std::cin);
  Polynomial p = list.eval();
  print_polynomial(p);
  return 0;
}
