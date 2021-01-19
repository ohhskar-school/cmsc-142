#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "loop.hpp"
#include "poly.hpp"

std::string readFile(std::ifstream &input);
int main() {

  // Opening File
  // std::string fileName;
  // std::cout << "Enter the name of the input file" << std::endl;
  // std::cin >> fileName;
  std::ifstream input("inputFile.txt");

  // Creating strings from file;
  std::string cleanedFile = readFile(input);
  std::cout << cleanedFile << std::endl;

  // Poly fileCount;
  // tokenizeLoops(loopHolder, fileCount);

  // Print final count of file
  // std::cout << "T(n) = ";
  // fileCount.printTerms();

  return 0;
}

// Reads the file and appends it to a string. Making it one line for easier
// tokenizing
std::string readFile(std::ifstream &input) {
  std::string fileContent;
  if (input.is_open()) {
    // Creating the buffer string
    std::string lines;

    // Reading each line
    while (getline(input, lines)) {
      lines.erase(std::remove(lines.begin(), lines.end(), '\r'), lines.end());
      fileContent.append(lines);
    }
  }

  fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), ' '),
                    fileContent.end());
  return fileContent;
}
