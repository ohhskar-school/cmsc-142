#include "procedure.hpp"
#include "loop.hpp"

#define IF_LENGTH 2
#define FOR_LENGTH 3
#define ELSE_LENGTH 4

#define TYPE_IF 20
#define TYPE_FOR 30
#define TYPE_ELSE 40

Procedure::Procedure() {}

void Procedure::tokenize(std::string file) {
  _workingString = file;

  size_t pos = _workingString.find("for", 0);

  while (pos != std::string::npos) {
    Parts newPos = _findParts(pos, TYPE_FOR, FOR_LENGTH);
    _forParts.push_back(newPos);
    pos = _workingString.find("for", newPos.endPos);
  }

  pos = _workingString.find("if", 0);

  while (pos != std::string::npos) {
    Parts newPos = _tokenizeIf(pos);
    _ifParts.push_back(newPos);
    pos = _workingString.find("if", newPos.endPos);
  }

  _cleanParts();

  for (auto &part : _allParts) {
    std::cout << part.content << std::endl;
  }

  // Remove all placeholder text for counting remaining procedures
  _workingString.erase(
      std::remove(_workingString.begin(), _workingString.end(), '/'),
      _workingString.end());
}

Parts Procedure::_findParts(size_t pos, size_t type, size_t lengthOfChar) {
  // Find the closing parenthesis for the conditions. This is done to check if
  // the loop/statement is a one liner of if contained in brackets
  size_t initPos = type == TYPE_ELSE
                       ? pos + lengthOfChar
                       : _workingString.find(")", pos + lengthOfChar) + 1;
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
  newForPart.isFor = type == TYPE_FOR;
  newForPart.content = funcWorkingString.substr(pos, len);
  newForPart.startPos = pos;
  newForPart.endPos = endPos;

  size_t workingStringLen = endPos - pos + 1;

  // Replace all instances to prevent checking against nested statements
  _workingString.replace(pos, workingStringLen, workingStringLen, '/');

  return newForPart;
}

Parts Procedure::_tokenizeIf(size_t pos) {
  Parts ifPart = _findParts(pos, TYPE_IF, IF_LENGTH);
  Parts elsePart;
  bool foundElse = false;

  if (_workingString.find("else", ifPart.endPos + 1) == ifPart.endPos + 1) {
    foundElse = true;
    elsePart = _findParts(ifPart.endPos + 1, TYPE_ELSE, ELSE_LENGTH);
  }

  if (foundElse) {
    Parts newIfPart;

    // Store values for the struct
    newIfPart.isFor = false;
    newIfPart.content = ifPart.content.append(elsePart.content);
    newIfPart.startPos = ifPart.startPos;
    newIfPart.endPos = elsePart.endPos;

    size_t workingStringLen = elsePart.endPos - pos + 1;

    // Replace all instances to prevent checking against nested statements
    _workingString.replace(pos, workingStringLen, workingStringLen, '/');

    return newIfPart;
    return ifPart;
  } else {
    return ifPart;
  }
}

// Checks if there are any nested for loops in the selections and places them
// back in the if statements.
void Procedure::_cleanParts() {
  for (auto &ifPart : _ifParts) {
    // Skip if no nested loops are found
    size_t pos = ifPart.content.find('/', 0);
    while (pos != std::string::npos) {
      auto i = std::begin(_forParts);

      // https://stackoverflow.com/questions/10360461/removing-item-from-vector-while-in-c11-range-for-loop
      while (i != std::end(_forParts)) {
        if (i->startPos > ifPart.startPos && i->endPos < ifPart.endPos) {
          ifPart.content.replace(pos, i->content.length(), i->content);
          i = _forParts.erase(i);
          break;
        } else {
          ++i;
        }
      }

      pos = ifPart.content.find('/', pos + 1);
    }
  }

  // https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
  _allParts.reserve(_ifParts.size() + _forParts.size());
  _allParts.insert(_allParts.end(), _forParts.begin(), _forParts.end());
  _allParts.insert(_allParts.end(), _ifParts.begin(), _ifParts.end());
}

void Procedure::_countProcedures() {
  int count = 0;
  const size_t procedureLength = _workingString.length();
  for (size_t j = 0; j < procedureLength; ++j) {
    if ((_workingString[j] == '+' || _workingString[j] == '-' ||
         _workingString[j] == '*' || _workingString[j] == '/' ||
         _workingString[j] == '=' || _workingString[j] == '>' ||
         _workingString[j] == '<') &&
        !(_workingString[j - 1] == '+' || _workingString[j - 1] == '-' ||
          _workingString[j - 1] == '*' || _workingString[j - 1] == '/' ||
          _workingString[j - 1] == '=' || _workingString[j - 1] == '<' ||
          _workingString[j - 1] == '>')) {
      count++;
    }
  }

  Term simpleCount(count, 0);
  _polyCount.append(simpleCount);
}

void Procedure::_countLoops() {
  for (auto &forPart : _forParts) {
    std::list<Term> termHolder;
    _holder = new Loop();
    _holder->tokenize(forPart.content);
    _holder->count();
    _holder->getCount().printTerms();
    termHolder = _holder->getCount().getTerms();

    for (auto &terms : termHolder) {
      _polyCount.append(terms);
    }
  }
}

void Procedure::count() {
  _countLoops();
  _countProcedures();
}

void Procedure::printCount() {
  std::cout << "T(n) = ";
  _polyCount.printTerms();
}

Poly Procedure::getCount() const { return _polyCount; }
