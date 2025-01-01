#include <iostream>
#include <vector>
#include "parser.cpp"
#include "numEx.cpp"

int main(int argc, const char* argv[]) {
  std::cout << "Hello World!" << std::endl;
  char c;
  std::vector<int> v = {8, 4, 5, 9};
  Ex* num = new NumEx(6);
  Polynomial p = num->eval();
  std::cout << p.value << std::endl;
  //std::vector<int> result = {1};
  Parser::consume_whitespace(&std::cin);
  c = std::cin.peek();
  std::cout << c << std::endl;
  c = std::cin.get();
  std::cout << c << std::endl;
  c = std::cin.get();
  std::cout << c << std::endl;
  delete num;
  return 0;
}
