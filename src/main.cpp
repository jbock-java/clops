#include <iostream>
#include <vector>
#include <memory>
#include <unistd.h>
#include <stdlib.h>

#include "parser.cpp"
#include "token.cpp"
#include "polynomial.cpp"

static const char* USAGE = R"""(Usage: clops [OPTIONS]
Read univariate polynomial expression from stdin.
Features:
  - polynomial multiplication
OPTIONS:
  -h    : Show usage info.
  -x <t>: use <t> as variable name.
          Default variable name is 'x'.
EXAMPLES:
  clops -xt <<< '(t + 1)(t - 1)'
)""";

int main(int argc, char** argv) {
  std::string x = "x";
  int c;
  while ((c = getopt(argc, argv, "x:h")) != -1) {
    switch (c) {
      case 'x':
        x = optarg;
        if (x.empty() || x.size() >= 2) {
          std::cout << "Option -x: Expecting single character argument\n";
          return 0;
        }
        break;
      case 'h':
        std::cout << USAGE;
        return 0;
      case '?':
        std::cout << "Option -h shows the available options.\n";
        return 1;
    }
  }
  std::shared_ptr<ListToken> result = Parser::parse(x.at(0), std::cin);
  std::unique_ptr<Polynomial> p = result->eval();
  p->print_polynomial(x.at(0));
  std::cout << '\n';
  return 0;
}
