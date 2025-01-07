#pragma once

#include <iostream>
#include "token.hpp"

namespace Parser {

  void parse(char x, ListToken& result, std::istream& in);
}

