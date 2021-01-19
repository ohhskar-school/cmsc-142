#ifndef MPA2_CONDITION
#define MPA2_CONDITION

#include <algorithm>
#include <string>

class Condition {
private:
  bool _isNumber;            // Stores if the condition is a number
  int _conditionType;        // Condition type i.e. <, >, <=
  int _conditionNumber;      // Condition if it is a number
  std::string _conditionVar; // Condition if it is a variable

  bool _isRoot;    // a bool to check if the operator is logarithmic
  int _rootNumber; // Stores the root number, ie 2 if sqr root;

  bool _checkIfStringIsNumber(std::string &s);

public:
  Condition();

  enum Conditions { less = 1 << 0, greater = 1 << 1, equal = 1 << 2 };
  int getCount() const;
  bool getIsNumber() const;
  bool getIsRoot() const;
  int getRootNumber() const;
  int getConditionType() const;
  int getConditionNumber() const;
  std::string getConditionVar() const;

  void tokenize(std::string rawCondition);
};

#endif
