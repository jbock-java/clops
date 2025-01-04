#pragma once

#include <iostream>
#include <memory>
#include "ex.hpp"

class Parser {

public:
  static void parse(ListEx& result, std::istream& in);
};

