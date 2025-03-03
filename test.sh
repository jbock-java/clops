#!/bin/bash

set -e

RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

expect() {
  local RESULT=$(./clops <<< "$2"$'\nq')
  if [[ "$RESULT" != "$1" ]]; then
    printf "${RED}=== FAILURE ===${NC}\n"
    echo "Expecting"
    echo ">>>"
    echo "$2"
    echo "<<<"
    echo "to evaluate to"
    echo ">>>"
    echo "$1"
    echo "<<<"
    echo "but found:"
    echo ">>>"
    echo "$RESULT"
    echo "<<<"
    return 1
  else
    printf "${GREEN}[OK]${NC} "
    printf "$2 -> $1\n"
    return 0
  fi
}

expect  "4"                 "2 + 2"
expect  "6"                 "2 * 3"
expect  "4 + 2x"            "2 (x + 2)"
expect "-1 + x^2"           "(x - 1) * (x + 1)"
expect  "1 + 2x + x^2"      "(x + 1) * (x + 1)"
expect  "1 + x + x^2 + x^3" "(x + 1) * (x^2 + 1)"
