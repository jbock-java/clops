#include <iostream>

class Parser {

  public: static void consume_whitespace(std::istream* in) {
    while(true) {
      char c = in->peek();
      if (c != ' ') {
        return;
      }
      in->get();
    }
  }
};

