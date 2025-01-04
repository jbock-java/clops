#include <iostream>
#include <vector>
#include <memory>

#include "parser.cpp"
#include "ex.cpp"
#include "polynomial.cpp"

int main(int argc, const char* argv[]) {
  ListEx result;
  Parser::parse(result, std::cin);
  std::unique_ptr<Polynomial> p = result.eval();
  p->print_polynomial();
  std::cout << '\n';
  return 0;
}
