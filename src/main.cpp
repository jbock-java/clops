#include <iostream>
#include <vector>
#include "parser.cpp"
#include "ex.cpp"

int main(int argc, const char* argv[]) {
  ListEx list = Parser::parse(&std::cin);
  Polynomial p = list.eval();
  std::cout << p.value << std::endl;
  return 0;
}
