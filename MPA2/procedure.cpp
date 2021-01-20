#include "procedure.hpp"

#define IF_LENGTH 2
#define FOR_LENGTH 3
#define ELSE_LENGTH 4

Procedure::Procedure() {}

void Procedure::tokenize(std::string file) {
  _workingString = file;

  size_t pos = _workingString.find("for", 0);

  while (pos != std::string::npos) {
    Parts newPos = _tokenizeFor(pos);
    _allParts.push_back(newPos);
    pos = _workingString.find("for", newPos.endPos);
  }

  for (auto &part : _allParts) {
    std::cout << part.content << std::endl;
  }
}

Parts Procedure::_tokenizeFor(size_t pos) {
  // Find the closing parenthesis for the conditions. This is done to check if
  // the loop is a one liner of if contained in brackets
  size_t initPos = _workingString.find(")", pos + FOR_LENGTH) + 1;
  size_t endPos = 0;
  size_t len = 0;

  // Create new workingString inside func. This is done so that the following
  // cycles will not invalidate previous positions found
  std::string funcWorkingString = _workingString;

  // If for is a one liner
  if (_workingString[initPos] != '{') {
    // Insert { at the start of the expression
    funcWorkingString.insert(initPos, 1, '{');

    size_t workingEndPos = funcWorkingString.find(";", initPos);

    // Since only 1 character was added, endPos is adjusted
    endPos = workingEndPos - 1;

    // Insert } at the start of the expression
    funcWorkingString.insert(workingEndPos + 1, 1, '}');

    // Account for extra additional }
    len = workingEndPos - pos + 2;

  } else {
    std::vector<size_t> bracketPositions;

    // Algo to check if balanced, if it is balanced, break as the last bracket
    // is the pair
    for (size_t i = initPos; i < _workingString.length(); ++i) {
      if (_workingString[i] == '{') {
        bracketPositions.push_back(i);
      } else if (_workingString[i] == '}') {
        endPos = i;
        bracketPositions.pop_back();
      }
      if (bracketPositions.size() == 0) {
        break;
      }
    }

    len = endPos - pos + 1;
  }

  Parts newForPart;

  // Store values for the struct
  newForPart.isFor = true;
  newForPart.content = funcWorkingString.substr(pos, len);
  newForPart.startPos = pos;
  newForPart.endPos = endPos;

  size_t workingStringLen = endPos - pos + 1;

  // Replace all instances to prevent checking against nested statements
  _workingString.replace(pos, workingStringLen, workingStringLen, '/');

  return newForPart;
}

// Parts Procedure::_tokenizeIf(size_t pos) {

//   if (_workingString.find("else", endPos + 1) == endPos + 1) {
//   }

//   Parts newForPart;

//   // Store values for the struct
//   newForPart.isFor = true;
//   newForPart.content = _workingString.substr(pos, len);
//   newForPart.startPos = pos;
//   newForPart.endPos = endPos;

//   // Replace all instances to prevent checking against nested statements
//   _workingString.replace(pos, len, newForPart.content.length(), '/');

//   return newForPart;
// }
