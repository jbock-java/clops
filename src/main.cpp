#include <iostream>
#include <vector>
#include "parser.cpp"
#include "ex.cpp"

int main(int argc, const char* argv[]) {
  char c;
  ListEx list{};
  NumEx num{6};
  list.add(num);
  Polynomial p = list.eval();
  std::cout << p.value << std::endl;
  //std::vector<int> result = {1};
  Parser::consume_whitespace(&std::cin);
  c = std::cin.peek();
  std::cout << c << std::endl;
  c = std::cin.get();
  std::cout << c << std::endl;
  c = std::cin.get();
  std::cout << c << std::endl;
  return 0;
}
