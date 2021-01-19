#ifndef MPA2_TERM
#define MPA2_TERM

#include <iostream>
#include <string>

class Term {

public:
  Term();
  Term(int coefficient, int exponent);
  Term(int coefficient, int exponent, char variable);
  Term(bool isInfinite);
  int getCoefficient() const;
  int getCoefficientDenominator() const;
  double getExponent() const;
  bool getIsInfinite() const;
  std::string getVariable() const;

  bool addCoefficient(int x);
  bool multiplyTerm(Term &input);
  bool divide(int divisor);

  bool applySummation(bool isUpperLimitNumber, bool isLogarithmic, bool isRoot,
                      int lowerLimit, int upperLimitInt,
                      std::string upperLimitString);

private:
  bool _infinite;
  int _coefficient;
  int _coefficientDenominator;
  double _exponent;
  std::string _variable;
};

#endif
