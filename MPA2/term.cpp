#include "term.hpp"

Term::Term() {
  _infinite = false;
  _coefficient = 1;
  _coefficientDenominator = 1;
  _exponent = 1;
  _variable = '(';
}

Term::Term(int coefficient, int exponent) {
  _infinite = false;
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  _variable = 'x';
  _coefficientDenominator = 1;
}

Term::Term(int coefficient, int exponent, char variable) {
  _infinite = false;
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  this->_variable = variable;
  _coefficientDenominator = 1;
}

Term::Term(bool isInfinite) {
  _infinite = isInfinite;
  _exponent = 10000000;
}

int Term::getCoefficient() const { return _coefficient; }

int Term::getCoefficientDenominator() const { return _coefficientDenominator; }

double Term::getExponent() const { return _exponent; }

std::string Term::getVariable() const { return _variable; }

bool Term::getIsInfinite() const { return _infinite; }

bool Term::addCoefficient(int x) {
  _coefficient += x;
  if (_coefficient % _coefficientDenominator == 0) {
    _coefficient /= _coefficientDenominator;
    _coefficientDenominator = 1;
  }
  return true;
}

bool Term::multiplyTerm(Term &input) {
  _exponent += input.getExponent();
  _coefficient *= input.getCoefficient();
  return true;
}

bool Term::divide(int divisor) {
  if (_exponent != 0) {
    if (_coefficient % divisor != 0) {
      _coefficientDenominator = divisor;

      if ((_coefficientDenominator < 0 && _coefficient < 0) ||
          (_coefficientDenominator < 0 && _coefficient >= 0)) {
        _coefficientDenominator *= -1;
        _coefficient *= -1;
      }
    } else {
      _coefficient /= divisor;
    }
  }

  return true;
}

bool Term::applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                          bool isRoot, int lowerLimit, int upperLimitInt,
                          std::string upperLimitString) {

  if (isRoot) {
    _exponent = 1.0 / static_cast<double>(upperLimitInt);
    _variable = upperLimitString;

  } else if (isLogarithmic) {
    _variable = upperLimitString;
    _exponent = -upperLimitInt;

  } else if (isUpperLimitNumber) {
    // Checking if lowerLimit is is less than the upperlimit
    if (lowerLimit > upperLimitInt) {
      _coefficient = 0;
      _exponent = 0;
      return true;
    }

    // Checking if the lowerLimit is not equal to 1, then normalizes it
    if (lowerLimit != 1) {
      upperLimitInt = upperLimitInt - lowerLimit + 1;
      lowerLimit = 1;
    }

    // Checking if the content of the term is constant
    if (_exponent == 0) {
      _coefficient *= upperLimitInt;
      return true;
    }
  } else {
    _exponent = _variable == upperLimitString ? _exponent + 1 : 1;
    _variable = upperLimitString;
    return true;
  }

  return false;
}

bool Term::operator<(Term &comp) {
  if (_exponent == comp._exponent) {
    double coefficient = _coefficient / _coefficientDenominator;
    double compCoefficient = comp._coefficient / comp._coefficientDenominator;

    return coefficient < compCoefficient;
  } else {
    double exponent = _exponent;
    double compExponent = comp._exponent;

    if (_exponent > 0 && _exponent < 1) {
      exponent = -_exponent;
    }

    if (comp._exponent > 0 && comp._exponent < 1) {
      compExponent = -comp._exponent;
    }

    return exponent < compExponent;
  }
}
