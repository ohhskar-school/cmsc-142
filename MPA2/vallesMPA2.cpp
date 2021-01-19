#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "loop.hpp"
#include "poly.hpp"

void readFile(std::ifstream &input, std::list<std::string> &loopHolder);
void tokenizeLoops(std::list<std::string> &loopHolder, Poly &fileCount);
int main() {

  // Opening File
  std::string fileName;
  std::cout << "Enter the name of the input file" << std::endl;
  std::cin >> fileName;
  std::ifstream input(fileName);

  Poly test;

  // Creating strings from file;
  std::list<std::string> loopHolder;
  readFile(input, loopHolder);
  Poly fileCount;
  tokenizeLoops(loopHolder, fileCount);

  // Print final count of file
  std::cout << "T(n) = ";
  fileCount.printTerms();

  return 0;
}

// Reads the file and appends it to a string. Making it one line for easier
// tokenizing
void readFile(std::ifstream &input, std::list<std::string> &loopHolder) {
  std::string fileContent;
  int forCounter = 0;
  int foundFor = false;
  if (input.is_open()) {

    // Creating the buffer string
    std::string lines;

    // Reading each line
    while (getline(input, lines)) {
      if (lines.find("for") != std::string::npos) {
        foundFor = true;
        forCounter++;
      }
      if (foundFor) {
        if (forCounter > 0) {
          lines.erase(std::remove(lines.begin(), lines.end(), '\r'),
                      lines.end());
          fileContent.append(lines);
        }
        if (lines.find("}") != std::string::npos) {
          forCounter--;
        }
        if (forCounter == 0) {
          foundFor = false;
          fileContent.erase(
              std::remove(fileContent.begin(), fileContent.end(), ' '),
              fileContent.end());
          std::cout << fileContent << std::endl;
          loopHolder.push_back(fileContent);
          fileContent.clear();
        }
      }
    }
  }
}

void tokenizeLoops(std::list<std::string> &loopHolder, Poly &fileCount) {
  for (auto &i : loopHolder) {
    Loop holder;
    std::list<Term> termHolder;
    holder.tokenize(i);
    holder.count();
    termHolder = holder.getCount().getTerms();
    for (auto &j : termHolder) {
      fileCount.append(j);
    }
  }
}
