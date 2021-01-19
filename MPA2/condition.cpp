#include "condition.hpp"

Condition::Condition() {
  _isNumber = true;
  _isRoot = false;
  _conditionType = 0;
  _conditionNumber = 0;
  _rootNumber = 1;
}

// 1 for the condition + the number of multiplications done, since _rootNumber
// starts with one, it is the only thing that  needs to be returned as the
// original formulae is  1 + (_rootNumber - 1)
int Condition::getCount() const { return _rootNumber; }

bool Condition::getIsRoot() const { return _isRoot; }

bool Condition::getIsNumber() const { return _isNumber; }

int Condition::getRootNumber() const { return _rootNumber; }

int Condition::getConditionType() const { return _conditionType; }

int Condition::getConditionNumber() const { return _conditionNumber; }

std::string Condition::getConditionVar() const { return _conditionVar; }

void Condition::tokenize(std::string rawCondition) {

  // Saves the length of the string so that the function will not be called
  // again
  const int rawConditionLength = rawCondition.length();

  bool foundCondition = false;
  std::string conditionHolder;

  // Loops through the string
  for (int i = 0; i < rawConditionLength; i++) {

    // Checks through every character in the string
    switch (rawCondition[i]) {
    case '<': {
      _conditionType = Conditions::less;
      foundCondition = true;
      break;
    }

    case '>': {
      _conditionType = Conditions::greater;
      foundCondition = true;
      break;
    }

    case '=': {
      if (_conditionType != 0) {
        // Adds the representation of equal to the condition type
        _conditionType = _conditionType | Conditions::equal;
      } else {
        _conditionType = Conditions::equal;
      }
      foundCondition = true;
      break;
    }

    // If multiplication is found, then that means the count is square root,
    // svaes the number of times the iterator was multiplied;
    case '*': {
      _isRoot = true;
      _rootNumber++;
    }

      // If a character that is not found in the cases above, then that means it
      // must be the iterator or the upper / lower limit depending on the
      // condition. To get the upper / lower limit, we  first check if the
      // condition is found. If it is found then that means the rest of the
      // string is the upper/lower limit

    default:
      if (foundCondition) {
        conditionHolder = rawCondition.substr(i, rawConditionLength - 1);
        if (_checkIfStringIsNumber(conditionHolder)) {
          _conditionNumber = std::stoi(conditionHolder);
        } else {
          _conditionVar = conditionHolder;
          _isNumber = false;
        }

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

bool Condition::_checkIfStringIsNumber(std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
