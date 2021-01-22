#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;
void includeMe(string, unordered_set<string> &);
int main() {

  // Creating input file
  string initialName;

  cin >> initialName;

  // Creating vector of already opened file
  unordered_set<string> filenames;

  includeMe(initialName, filenames);

  return 0;
}

void includeMe(string fileName, unordered_set<string> &fileNames) {

  pair<unordered_set<string>::iterator, bool> result;
  result = fileNames.insert(fileName);

  if (!result.second) {
    return;
  }

  // Creating initial input stream
  ifstream input(fileName);

  // Working on file if it is open
  if (input.is_open()) {

    // Creating buffer string for each line
    string lines;

    // Iterating through the lines
    while (getline(input, lines)) {

      // Checking to see if #include is in the current line
      if (lines.find("#include") != string::npos) {

        // With help from
        // https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
        // for tokenizing strings
        istringstream tempStream(lines);
        string token;

        int counter = 0;
        while (std::getline(tempStream, token, '"')) {
          // Skips the first tokenization as it is the #include" string
          if (counter == 1) {
            includeMe(token, fileNames);
            break;
          } else {
            counter++;
          }
        }
      }

      // If #include is not found in the statement, the contents of the file is
      // written to the output
      else {
        std::cout << lines << endl;
      }
    }
  }

  input.close();
}
