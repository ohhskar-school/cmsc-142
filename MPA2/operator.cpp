#include "operator.hpp"
#include <iostream>

Operator::Operator() {
  _operatorType = Operators::none;
  _operatorNumber = 0;
}

// Since all operators only take 1 unit of time, it will always return 1
int Operator::getCount() const { return 1; }

int Operator::getOperatorType() const { return _operatorType; }

int Operator::getOperatorNumber() const { return _operatorNumber; }

void Operator::tokenize(std::string rawOperator) {

  // Saves the length of the string so that the function will not be called
  // again
  const int rawOperatorLength = rawOperator.length();

  bool foundOperator = false;
  std::string operatorHolder;

  // Loops through the string
  for (int i = 0; i < rawOperatorLength; i++) {

    // Checks through every character in the string
    switch (rawOperator[i]) {

    case '+': {
      // If operatorType is already Operators::add, then that means that the
      // previous character was a +, which  means that the string contains ++,
      // which is += 1. since both operator type and numbers are found, breaks
      // the loop using goto, as using  break will break from the switch, not
      // from the  loop
      if (_operatorType == Operators::add) {
        _operatorNumber = 1;
        goto end;
      } else {
        _operatorType = Operators::add;
      }
      break;
    }

    case '-': {
      // Same logic as +
      if (_operatorType == Operators::subtract) {
        _operatorNumber = 1;
        goto end;
      } else {
        _operatorType = Operators::subtract;
      }
      break;
    }

    case '*': {
      _operatorType = Operators::multiply;
      break;
    }

    case '/': {
      _operatorType = Operators::divide;
      break;
    }

    // if = is found then that means that the operator was already found
    case '=': {
      foundOperator = true;
      break;
    }

    default:
      if (foundOperator) {
        operatorHolder = rawOperator.substr(i, rawOperatorLength - 1);
        _operatorNumber = std::stoi(operatorHolder);

        // Ends the loop. Break cannot work here as it will only break from the
        // switch, not from the loop
        goto end;
      } else {
        break;
      }
    }
  }

end:
  return;
}
