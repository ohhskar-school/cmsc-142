#ifndef MPA2_PROCEDURE
#define MPA2_PROCEDURE

#include "poly.hpp"
#include <algorithm>
#include <string>
#include <vector>

class Loop;
class If;

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
  void count();
  void printMembers();
  void printCount();
  Poly getCount() const;

private:
  std::vector<Parts> _ifParts;
  std::vector<Parts> _forParts;
  std::vector<Parts> _allParts;
  std::string _workingString;

  Parts _tokenizeIf(size_t);
  Parts _findParts(size_t, size_t, size_t);
  void _cleanParts();

  Loop *_loopHolder;
  If *_ifHolder;
  Poly _polyCount;
  void _countLoops();
  void _countIf();
  void _countProcedures();
};

#endif
