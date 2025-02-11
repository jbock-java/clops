#pragma once

#include <iostream>
#include "token.hpp"

namespace Parser {

  std::unique_ptr<ListToken> parse(char x, std::istream& in);
}

