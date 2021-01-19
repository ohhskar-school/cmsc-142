#include "procedure.hpp"

void Procedure::tokenize(std::string file) {
  std::vector<std::string> forStrings;
  std::vector<std::string> ifStrings;

  size_t pos = file.find("for", 0);

  while (pos != std::string::npos) {
    // finding end of for
    std::vector<size_t> bracketPositions;
    size_t initPos = file.find("{", pos + 1);
  }
}
