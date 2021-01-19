#include "iterator.hpp"

std::string Iterator::getIterator() const { return _iterator; }

std::string Iterator::tokenize(std::string rawIterator) {

  // Creating buffer variables
  std::istringstream tempStream(rawIterator);
  std::string token;
  int counter = 0;

  // Gets the string before the assignment operator and returns the remaining
  // string
  while (std::getline(tempStream, token, '=')) {
    switch (counter) {
    case 0:
      _iterator = token;
      break;
    case 1:
      return token;
    default:
      break;
    }

    counter++;
  }

  return "";
}
