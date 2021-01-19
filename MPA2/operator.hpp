#ifndef MPA2_OPERATOR
#define MPA2_OPERATOR

#include <string>

class Operator {
private:
  int _operatorType;   // Operator type i.e. +, -, =
  int _operatorNumber; // The value that is being used to modify the iterator

public:
  Operator();

  enum Operators { none, add, subtract, multiply, divide };
  int getCount() const;
  int getOperatorType() const;
  int getOperatorNumber() const;
  void tokenize(std::string rawOperator);
};

#endif
