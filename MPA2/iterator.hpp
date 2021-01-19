#ifndef MPA2_ITERATOR
#define MPA2_ITERATOR

#include <sstream>
#include <string>

class Iterator {
private:
  std::string _iterator;

public:
  std::string getIterator() const;
  std::string tokenize(std::string rawIterator);
};

#endif
