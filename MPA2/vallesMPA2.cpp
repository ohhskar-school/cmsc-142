#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "procedure.hpp"

#include "loop.hpp"
#include "poly.hpp"

#define IS_SUBMISSION true

std::string readFile(std::ifstream &input);
std::string readFromCin();
int main() {

  // Opening File
  // std::string fileName;
  // std::cout << "Enter the name of the input file" << std::endl;
  // std::cin >> fileName;
  std::string cleanedFile;

  if (IS_SUBMISSION) {
    cleanedFile = readFromCin();
  } else {
    std::ifstream input("inputFile.txt");
    cleanedFile = readFile(input);
  }

  Procedure file;
  file.tokenize(cleanedFile);
  file.count();
  file.printCount();

  // Poly fileCount;
  // tokenizeLoops(loopHolder, fileCount);

  // Print final count of file
  // std::cout << "T(n) = ";
  // fileCount.printTerms();

  return 0;
}

// Converts the entire file into one string
std::string readFile(std::ifstream &input) {
  std::string fileContent;
  int lineCount = -1;

  if (input.is_open()) {
    // Creating the buffer string
    std::string lines;

    // Reading each line
    while (getline(input, lines)) {
      // Get initial line count
      if (lineCount == -1) {
        lineCount = std::stoi(lines);
      }

      // If lines are still present but exceed the number of line, dont include
      // the extra lines

      // Append lines to one string
      else {
        lines.erase(std::remove(lines.begin(), lines.end(), '\r'), lines.end());
        fileContent.append(lines);
        --lineCount;
        if (lineCount == 0) {
          break;
        }
      }
    }
  }

  // remove all spaces
  fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), ' '),
                    fileContent.end());
  return fileContent;
}

std::string readFromCin() {

  std::string fileContent;
  int lineCount = -1;

  // Creating the buffer string
  std::string lines;

  // Reading each line
  while (getline(std::cin, lines)) {
    // Get initial line count
    if (lineCount == -1) {
      lineCount = std::stoi(lines);
    } else {
      lines.erase(std::remove(lines.begin(), lines.end(), '\r'), lines.end());
      fileContent.append(lines);
      --lineCount;

      if (lineCount == 0) {
        break;
      }
    }
  }

  // remove all spaces
  fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), ' '),
                    fileContent.end());
  return fileContent;
}
