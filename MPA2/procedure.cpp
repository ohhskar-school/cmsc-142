#include "procedure.hpp"

#define FOR_LENGTH 3
#define IF_LENGTH 2

Procedure::Procedure() {}

void Procedure::tokenize(std::string file) {
  std::string workingString = file;
  std::vector<std::string> forStrings;
  std::vector<std::string> ifStrings;

  size_t pos = file.find("for", 0);

  // Find whole content of for
  while (pos != std::string::npos) {
    // Find the closing parenthesis for the conditions. This is done to check if
    // the loop is a one liner of if contained in brackets
    size_t initPos = file.find(")", pos + FOR_LENGTH) + 1;
    size_t endPos = 0;
    size_t len = 0;

    // If for is a one liner
    if (file[initPos] != '{') {
      // Insert { at the start of the expression
      file.insert(initPos, 1, '{');

      endPos = file.find(";", initPos);

      // Insert } at the start of the expression
      file.insert(endPos + 1, 1, '}');

      len = endPos - pos + 2;
    } else {
      std::vector<size_t> bracketPositions;

      // Algo to check if balanced, if it is balanced, break as the last bracket
      // is the pair
      for (size_t i = initPos; i < file.length(); ++i) {
        if (file[i] == '{') {
          bracketPositions.push_back(i);
        } else if (file[i] == '}') {
          endPos = i;
          bracketPositions.pop_back();
        }
        if (bracketPositions.size() == 0) {
          break;
        }
      }

      len = endPos - pos + 1;
    }

    forStrings.push_back(file.substr(pos, len));
    file.erase(pos, len);
    pos = file.find("for", pos);
  }

  for (auto &fr : forStrings) {
    std::cout << fr << std::endl;
  }
}
