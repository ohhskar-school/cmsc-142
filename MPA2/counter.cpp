#include "counter.hpp"

Counter::Counter() {
  _isNumber = true;
  _counterNumber = 0;
}

bool Counter::getIsNumber() const { return _isNumber; };

int Counter::getCounterNumber() const { return _counterNumber; };

std::string Counter::getCounterVar() const { return _counterVar; };

// Checks if rawCounter is a number and stores it in an int, if not, stores it
// in a string
void Counter::tokenize(std::string rawCounter) {
  if (_checkIfStringIsNumber(rawCounter)) {
    _counterNumber = std::stoi(rawCounter);
  } else {
    _counterVar = rawCounter;
    _isNumber = false;
  }
}

bool Counter::_checkIfStringIsNumber(std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
