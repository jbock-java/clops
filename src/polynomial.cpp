#include <iostream>
#include <sstream>

#include "polynomial.hpp"
#include "fraction.cpp"

std::string Polynomial::toString(char x) {
  std::stringstream sb;
  bool printed = false;
  for (size_t i = 0; i < coefficients.size(); i++) {
    if (coefficients[i]->isZero()) {
      continue;
    }
    if (printed) {
      sb << " + ";
    }
    printed = true;
    if (i == 0 || !coefficients[i]->isOne()) {
      sb << coefficients[i]->toString();
    }
    if (i != 0) {
      sb << x;
    }
    if (i != 0 && i != 1) {
      sb << '^' << std::to_string(i);
    }
  }
  return sb.str();
}

std::unique_ptr<Fraction> Polynomial::getCoefficient(size_t i) {
  if (i >= coefficients.size()) {
    return std::make_unique<Fraction>(0);
  }
  int numerator = coefficients[i]->numerator;
  int denominator = coefficients[i]->denominator;
  return std::make_unique<Fraction>(numerator, denominator);
}

size_t Polynomial::getDegree() {
  if (coefficients.empty()) {
    return 0;
  }
  return coefficients.size();
}

std::unique_ptr<Polynomial> Polynomial::add(Polynomial* other) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(std::max(getDegree(), other->getDegree()));
  for (size_t i = 0; i < coefficients.size(); i++) {
    result->coefficients.push_back(coefficients[i]->add(other->getCoefficient(i).get()));
  }
  for (size_t i = coefficients.size(); i < other->coefficients.size(); i++) {
    result->coefficients.push_back(other->getCoefficient(i));
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::monoMult(Fraction* coefficient, size_t degree) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(degree + getDegree());
  for (size_t i = 0; i < degree; i++) {
    result->coefficients.emplace_back(std::make_unique<Fraction>(0));
  }
  for (size_t i = 0; i < getDegree(); i++) {
    Fraction* f = coefficients[i].get();
    std::unique_ptr<Fraction> p = coefficient->mult(f);
    result->coefficients.push_back(std::move(p));
  }
  return result;
}

std::unique_ptr<Polynomial> Polynomial::mult(Polynomial* other) {
  std::unique_ptr<Polynomial> result = std::make_unique<Polynomial>(getDegree() + other->getDegree());
  for (size_t i = 0; i < other->coefficients.size(); i++) {
    std::unique_ptr<Polynomial> p = monoMult(other->coefficients[i].get(), i);
    result = result->add(p.get());
  }
  return result;
}
