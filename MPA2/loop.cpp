#include "loop.hpp"

Loop::Loop() { _innerLoop = nullptr; }
void Loop::tokenize(std::string file) {
  // Gets the next character after the parenthesis
  unsigned openParen = file.find("(") + 1;

  // Gets the length of the contents of the parenthesis by getting the position
  // of the close parenthesis and subtracting the number of characters from the
  // start of the loop declaration to the character after the first parenthesis
  unsigned parenLen = file.find(")") - openParen;

  // Gets the next character after the close bracket;
  unsigned openBracket = file.find("{") + 1;

  // Same logic is follewed from parenLen
  unsigned bracketLen = file.find_last_of("}") - openBracket;

  // Gets the content of the parenthesis

  std::string parenContent = file.substr(openParen, parenLen);
  std::string bracketContent = file.substr(openBracket, bracketLen);

  _tokenizeParenContent(parenContent);
  _tokenizeBracketContent(bracketContent);
}

void Loop::_tokenizeParenContent(std::string &parenContent) {

  // Creating buffer variables
  std::istringstream tempStream(parenContent);
  std::string token;
  int counter = 0;

  // Tokenizing the string
  while (std::getline(tempStream, token, ';')) {
    switch (counter) {
    case 0:
      // Tokenizes the iterator which returns the counter, which is then
      // tokenized;
      _counter.tokenize(_iterator.tokenize(token));
      break;
    case 1:
      _condition.tokenize(token);
      break;
    case 2:
      _operator.tokenize(token);
      break;
    default:
      break;
    }

    counter++;
  }
}

void Loop::_tokenizeBracketContent(std::string &bracketContent) {
  // Creating buffer variables

  const size_t forLocation = bracketContent.find("for");
  if (forLocation != std::string::npos) {
    const size_t endLocation = bracketContent.find("}");
    std::string forString =
        bracketContent.substr(forLocation, endLocation - forLocation + 1);

    bracketContent =
        bracketContent.erase(forLocation, endLocation - forLocation + 1);
    Loop *innerLoop = new Loop;
    innerLoop->tokenize(forString);
    innerLoop->count();
    _innerLoop = innerLoop;
  }

  std::istringstream tempStream(bracketContent);
  std::string token;
  while (std::getline(tempStream, token, ';')) {
    _procedures.push_back(token);
  }
}

void Loop::printMembers() {
  for (auto &i : _procedures) {
    std::cout << i << std::endl;
  }
  std::cout << std::endl;
}

void Loop::count() {
  bool isInfinite = false;
  // Counts the procedures + condition + operator
  if (_counter.getIsNumber()) {
    if ((!_condition.getIsNumber() &&
         _operator.getOperatorType() == Operator::Operators::subtract) ||

        // counter < condition && condition is less && operator is subtract
        ((_counter.getCounterNumber() < _condition.getConditionNumber()) &&
         (_condition.getConditionType() & Condition::Conditions::greater) &&
         (_operator.getOperatorType() == Operator::Operators::add))) {
      Term infinite(true);
      _polyCount.append(infinite);
    }

    if (!isInfinite) {
      Term inLoop(
          _countProcedures() + _condition.getCount() + _operator.getCount(), 0);

      _polyCount.append(inLoop);

      // If root handle as root
      if (_condition.getIsRoot()) {
        _polyCount.applySummation(
            false, false, true, _counter.getCounterNumber(),
            _condition.getRootNumber(), _condition.getConditionVar());
      }
      // If counter is a number, condition is not and operator is multiply
      else if ((!_condition.getIsNumber()) &&
               (_operator.getOperatorType() == Operator::Operators::multiply)) {
        _polyCount.applySummation(
            true, true, false, _counter.getCounterNumber(),
            _operator.getOperatorNumber(), _condition.getConditionVar());
      }

      // If counter is a number but condition is not
      else if (!_condition.getIsNumber()) {
        _polyCount.applySummation(false, false, false,
                                  _counter.getCounterNumber(), 0,
                                  _condition.getConditionVar());
      }
      // If both the counter and condition are numbers
      else if (_condition.getIsNumber()) {
        _polyCount.applySummation(true, false, false,
                                  _counter.getCounterNumber(),
                                  _condition.getConditionNumber(), "");
      }

      // Divides based on operatorNumber
      if (_operator.getOperatorType() == Operator::Operators::add) {
        _polyCount.divide(_operator.getOperatorNumber());
      }
    }
  }

  // Counts the creation of the iterator and the last condition check
  if (!isInfinite) {
    Term afterLoop(1 + _condition.getCount(), 0);
    _polyCount.append(afterLoop);
  }
}

int Loop::_countProcedures() {
  int count = 0;
  for (auto &procedure : _procedures) {
    const int procedureLength = procedure.length();
    for (int j = 0; j < procedureLength; j++) {
      if ((procedure[j] == '+' || procedure[j] == '-' || procedure[j] == '*' ||
           procedure[j] == '/' || procedure[j] == '=' || procedure[j] == '>' ||
           procedure[j] == '<') &&
          !(procedure[j - 1] == '+' || procedure[j - 1] == '-' ||
            procedure[j - 1] == '*' || procedure[j - 1] == '/' ||
            procedure[j - 1] == '=' || procedure[j - 1] == '<' ||
            procedure[j - 1 == '>'])) {
        count++;
      }
    }
  }
  return count;
}

void Loop::printCount() {
  std::cout << "T(n) = ";
  _polyCount.printTerms();
}

Poly Loop::getCount() const { return _polyCount; }
