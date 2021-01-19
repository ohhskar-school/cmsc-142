#include "procedure.hpp"

#define FOR_LENGTH 3
#define IF_LENGTH 2

Procedure::Procedure() {}

void Procedure::tokenize(std::string file) {
  std::vector<std::string> forStrings;
  std::vector<std::string> ifStrings;

  size_t pos = file.find("for", 0);

  // Find whole content of for
  while (pos != std::string::npos) {
    std::vector<size_t> bracketPositions;

    // Find the closing parenthesis for the conditions. This is done to check if
    // the loop is a one liner of if contained in brackets
    size_t initPos = file.find(")", pos + FOR_LENGTH) + 1;
    size_t endPos = 0;

    // 0 1 2 3 4
    // If one liner for
    if (file[initPos] != '{') {
      file.insert(initPos, 1, '{');
      endPos = file.find(";", initPos);
      file.insert(endPos + 1, 1, '}');
      forStrings.push_back(file.substr(pos, endPos - pos + 2));
    }

    pos = file.find("for", endPos + 1);
  }

  for (auto &fr : forStrings) {
    std::cout << fr << std::endl;
  }
}
