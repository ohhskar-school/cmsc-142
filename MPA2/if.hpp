#ifndef MPA2_IF
#define MPA2_IF

#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "poly.hpp"

class Procedure;

class If {
public:
  If();
  ~If();
  void tokenize(std::string file);
  void count();
  Poly getCount() const;

private:
  Procedure *_ifProcedure;
  Procedure *_elseProcedure;
  Procedure *_conditionProcedure;

  std::string _condition;
  std::string _if;
  std::string _else;
  Poly _polyCount;
};

#endif // MPA2_IF
