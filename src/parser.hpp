#pragma once

#include <iostream>
#include "ex.hpp"

class Parser {

public:
  static void consume_whitespace(std::istream* in);
  static ListEx parse(std::istream* in);
};

