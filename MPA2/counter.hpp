
#ifndef MPA2_COUNTER
#define MPA2_COUNTER

#include <algorithm>
#include <string>

class Counter {
private:
  bool _isNumber;          // Stores if the counter is a number
  int _counterNumber;      // Counter if it is a number
  std::string _counterVar; // Counter if it is a variable

  bool _checkIfStringIsNumber(std::string &s);

public:
  Counter();

  bool getIsNumber() const;
  int getCounterNumber() const;
  std::string getCounterVar() const;
  void tokenize(std::string rawCounter);
};

#endif
