#pragma once

#include <iostream>
#include "ex.hpp"

class Parser {

public:
  static void consume_whitespace(std::istream& in);
  static void parse(ListEx& result, std::istream& in);
private:
  static void parse(ListEx& result, std::istream& in, bool is_nested);
};

