#include <iostream>
#include <vector>
#include <memory>
#include <unistd.h>
#include <stdlib.h>

#include "parser.cpp"
#include "ex.cpp"
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
  char x = 'x';
  int c;
  while ((c = getopt(argc, argv, "x:h")) != -1) {
    std::string soptarg;
    switch (c) {
      case 'x':
        soptarg = optarg;
        if (soptarg.empty() || soptarg.size() >= 2) {
          std::cout << "Option -x: Expecting single character argument\n";
          return 0;
        }
        x = soptarg.at(0);
        break;
      case 'h':
        std::cout << USAGE;
        return 0;
      case '?':
        std::cout << "Option -h shows the available options.\n";
        return 1;
    }
  }
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    if (line == "q") {
      break;
    }
    std::unique_ptr<ListToken> result = Parser::parse(x, line);
    std::unique_ptr<Ex> transformed = result->transform();
    std::unique_ptr<Polynomial> p = transformed->eval();
    std::cout << p->toString(x) << '\n';
  }
  return 0;
}
