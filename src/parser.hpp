#pragma once

#include <iostream>
#include <memory>
#include "ex.hpp"

class Parser {

public:
  static void parse(char x, ListEx& result, std::istream& in);
};

