#ifndef MPA2_PROCEDURE
#define MPA2_PROCEDURE

#include "poly.hpp"
#include <algorithm>
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
  std::vector<Parts> _ifParts;
  std::vector<Parts> _forParts;
  std::vector<Parts> _allParts;
  std::string _workingString;

  Parts _tokenizeIf(size_t);
  Parts _findParts(size_t, size_t, size_t);
  void _cleanParts();

  Poly _polyCount;
  int _countProcedures();
};

#endif
