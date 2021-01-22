#include "if.hpp"
#include "procedure.hpp"

If::If() {
  _ifProcedure = nullptr;
  _elseProcedure = nullptr;
}

If::~If() {
  delete _ifProcedure;
  delete _elseProcedure;
}

void If::tokenize(std::string file) {
  // Get condition
  size_t startConditionPos = file.find('(', 0);
  size_t endConditionPos = file.find(')', startConditionPos + 1);

  _condition = file.substr(startConditionPos + 1,
                           endConditionPos - startConditionPos - 1);

  size_t startBracketPos = file.find('{', endConditionPos);
  size_t endBracketPos = file.find('}', startBracketPos + 1);

  _if = file.substr(startBracketPos + 1, endBracketPos - startBracketPos - 1);

  if (file.find("else", endBracketPos) != std::string::npos) {
    size_t startElseBracketPos = file.find('{', endBracketPos);
    size_t endElseBracketPos = file.find_last_of('}');

    _else = file.substr(startElseBracketPos + 1,
                        endElseBracketPos - startElseBracketPos - 1);
  }
}

Poly If::getCount() const { return _polyCount; }

void If::count() {
  // Count Conditions
  _ifProcedure = new Procedure;
  _ifProcedure->tokenize(_condition);
  _ifProcedure->count();

  std::list<Term> termHolder;
  termHolder = _ifProcedure->getCount().getTerms();

  for (auto &terms : termHolder) {
    _polyCount.append(terms);
  }

  delete _ifProcedure;
  _ifProcedure = new Procedure;
  _ifProcedure->tokenize(_if);
  _ifProcedure->count();

  if (_else.length() > 0) {
    _elseProcedure = new Procedure;
    _elseProcedure->tokenize(_else);
    _elseProcedure->count();
  }

  if (_elseProcedure != nullptr) {
    Poly elsePoly = _elseProcedure->getCount();
    Poly ifPoly = _ifProcedure->getCount();
    elsePoly.printTerms();
    ifPoly.printTerms();
    if (elsePoly < ifPoly) {
      std::list<Term> termHolder = ifPoly.getTerms();
      for (auto &terms : termHolder) {
        _polyCount.append(terms);
      }
    } else {
      std::list<Term> termHolder = elsePoly.getTerms();
      for (auto &terms : termHolder) {
        _polyCount.append(terms);
      }
    }
  } else {
    std::list<Term> termHolder = _ifProcedure->getCount().getTerms();
    for (auto &terms : termHolder) {
      _polyCount.append(terms);
    }
  }
}
