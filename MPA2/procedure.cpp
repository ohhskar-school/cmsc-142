#include "procedure.hpp"

void Procedure::tokenize(std::string file) {
  std::vector<std::string> forStrings;
  std::vector<std::string> ifStrings;

  size_t pos = file.find("for", 0);

  // Find whole content of for
  while (pos != std::string::npos) {
    std::vector<size_t> bracketPositions;
    size_t initPos = file.find("{", pos + 1);

    bracketPositions.push_back(initPos);
    for (size_t i = initPos + i; i < file.length(); ++i) {
    }
  }
}
