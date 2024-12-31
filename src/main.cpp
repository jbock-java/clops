#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char* argv[]) {
  cout << "Hello World!" << endl;
  char c;
  c = cin.peek();
  cout << c << endl;
  c = cin.get();
  cout << c << endl;
  c = cin.get();
  cout << c << endl;
  return 0;
}
