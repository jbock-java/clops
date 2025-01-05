#pragma once

#include <iostream>
#include <string>

class Polynomial {
public:
  virtual void print_polynomial(char x) = 0;
  virtual ~Polynomial() {}
};

class Poly final : public Polynomial {
public:
  std::vector<int> coefficients;
  void print_polynomial(char x) override;
  Poly() {
    coefficients.reserve(16);
  }
};

class Vary final : public Polynomial {
private:
  const int degree;
public:
  void print_polynomial(char x) override;
  Vary(int degree)
    : degree(degree)
  {}
};

class Consty final : public Polynomial {
private:
  const int coefficient;
public:
  void print_polynomial(char x) override;
  Consty(int coefficient)
    : coefficient(coefficient)
  {}
};
