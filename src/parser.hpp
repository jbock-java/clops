#pragma once

#include <iostream>
#include "token.hpp"

namespace Parser {

  std::shared_ptr<ListToken> parse(char x, std::istream& in);
}

