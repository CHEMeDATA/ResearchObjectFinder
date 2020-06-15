
#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// HERE : set up readding stdin... filelist...
using namespace std;
/*

# takes the excel sheet with tab sepration and makes code to insert in cpp
program
./compileList.sh
# extracts only the part of the zip file necessary for identification of objects
./do
# create the objets metadata
reset; clang++ acqus.cpp -o acqus.o ; ./acqus.o
"../data//62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt"

*/
bool testLine(string line, string testedString, int whereFistChar = 0) {
  if (whereFistChar == 0) {
    // search enaywhere in line
  } else {
    // get to the position and search strictly there
  }
  return true;  /// HERE
}

bool test(string currentFile, string testingName, int location, string what,
          int whereline = 0, int whereFistChar = 0, string supp = string("")) {
  // file true location
  string line = "";  /// HERE
  if (whereline != 0)
    // get to line of the file to test
    // if (whereFistChar) test anywhere in the line
    testLine(line, testingName, whereFistChar);
  else
    testLine(line, testingName, whereFistChar);

  return true;  /// HERE
}

int main(int argc, char **argv) {
#include "forCprogInit.txt"

  ifstream fileStream2;

  class Data {
   public:
    std::vector<double> x;
    std::vector<double> y;
  };
  Data data;
  for (int loop = 1; loop < argc; loop++) {
    data.x.clear();
    data.y.clear();

    fileStream2.open(argv[loop]);

    fileStream2.close();
  }

  // condition = condition && (   test(currentFile, "", 0, "2D", 2, 21));
  string currentFile = "";  /// HERE

  //   if(currFileName.compare(".out") == 0) {
  string currFileName = ".mol";  /// HERE
  bool condition = true;         // HERE
  int addme = -1;
  bool debug = true;
  for (int caseNumber = 1; caseNumber <= 32; caseNumber++) {
    // This is testing if current

    // if not first
    debug = 0;

#include "forCprog.txt"
    // dump crit if

    if (condition) {
      cout << "YES:::::: " << caseNumber << ": " << ObjTitle[caseNumber + addme]
           << " "
           << "FileKey: " << fileKey[caseNumber + addme] << " ";
    } else {
      cout << "NO        " << caseNumber << ": " << ObjTitle[caseNumber + addme]
           << " "
           << "FileKey: " << fileKey[caseNumber + addme] << " ";
    }
    cout << endl;
  }
}