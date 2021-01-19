#ifndef MPA2_PROCEDURE
#define MPA2_PROCEDURE

#include "poly.hpp"
#include <string>
#include <vector>

class Procedure {
public:
  Procedure();
  void tokenize(std::string);
  Poly getCount();

private:
  std::list<std::string> _procedures;

  Poly _polyCount;
  int _countProcedures;
};

#endif
