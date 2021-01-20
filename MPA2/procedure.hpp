#ifndef MPA2_PROCEDURE
#define MPA2_PROCEDURE

#include "poly.hpp"
#include <string>
#include <vector>

struct Parts {
  bool isFor;
  std::string content;
  size_t startPos;
  size_t endPos;
};

class Procedure {
public:
  Procedure();
  void tokenize(std::string);
  Poly getCount();

private:
  std::vector<Parts> _allParts;
  std::list<std::string> _procedures;
  std::string _workingString;

  Parts _tokenizeFor(size_t);
  Parts _tokenizeIf(size_t);

  Poly _polyCount;
  int _countProcedures;
};

#endif
