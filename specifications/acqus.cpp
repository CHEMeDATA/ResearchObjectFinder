
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
inline bool testLine(const string &line, const string &testedString, const  int &whereFistChar) {
  if (whereFistChar == 0) {
    return (line.find(testedString) != std::string::npos);
  } else {
  //  cout << " out of this... :  " << line << endl;
   // cout << " looked only there <"
    //     << line.substr(whereFistChar - 1, testedString.length()) << ">"
     //    << endl;
   // cout << " out of this cut ...testedString :  " << testedString << endl;

    return (line.substr(whereFistChar - 1, testedString.length()).find(testedString) != std::string::npos);
  }
}

bool test(const string &currentFile, const string &testingName,
          const int &location, string what = string(""), int whereline = 0,
          int whereFistChar = 0, string supp = string("")) {
  /*std::cout << "-------------------------------------- " << '\n';
  std::cout << "testing : " << currentFile << '\n';
  std::cout << "what : " << what << '\n';
  std::cout << "whereline : " << whereline << '\n';
  std::cout << "whereFistChar : " << whereFistChar << '\n';
  std::cout << "testingName : " << testingName << '\n';
  std::cout << "location : " << location << '\n';*/

  ifstream fileStream;
  bool found;
  // file true location

  // here takes into account change of file name...

  fileStream.open(currentFile);
  string line = "";
  // fast forward
  if (whereline > 0) {
    for (int i = 0; i < whereline - 1; i++) {
      if (!getline(fileStream, line)) {
        fileStream.close();
        return false;
      }
    }
 //   std::cout << "Reached the only tested line: " << whereline << '\n';
  }
  // central read
  if (!getline(fileStream, line)) {
    fileStream.close();
    return false;
  }
  //std::cout << "First tested line : " << line << '\n';

  // testing ...
  found = testLine(line, what, whereFistChar);
  if (found) {
   // std::cout << "found : " << what << '\n';
    return true;
  }
  if (whereline > 0) { // if only one line is tested
    return false;
  }

  for (int i = 0; true; i++) {
    if (!getline(fileStream, line)) {
      fileStream.close();
      return false;
    }
    found = testLine(line, what, whereFistChar);
    if (found ) {
      std::cout << "found : " << what << '\n';
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv) {
#include "forCprogInit.txt"
  bool condition;
  bool condition2;
  int addme;
  bool debug = true;
  bool debutStore;
  string currFileName = ".mol";  /// HERE
  string currentFile;
  /* class Data {
   public:
    std::vector<double> x;
    std::vector<double> y;
  };
  Data data;   data.x.clear();
    data.y.clear();
*/
  for (int loop = 1; loop < argc; loop++) {
    currentFile.clear();
    currentFile.assign(argv[loop]);
    currFileName.clear();
    currFileName.assign(argv[loop]);

    if (debug) {
      cout << "========================================================="
           << endl;
      cout << "Work on file: " << currentFile << endl;
    }
    for (int caseNumber = 1; caseNumber <= 32; caseNumber++) {
      condition = true;  
      condition2 = false;  

      // Prepare long list of test in forCprog.txt file...
      debutStore = debug;
      debug = false;
      if (loop == 1) debug = false;  // was true
     // std::cout << "++testing : " << currentFile << '\n';
      //std::cout << "++testingName : " << currFileName << '\n';

#include "forCprog.txt"
     //     cout << "condition  " << condition << ": " << endl;
     //     cout << "condition2 " << condition2 << ": " << endl;


condition = condition && condition2;

      /*  cout << "currFileName: " << currFileName << endl;
        cout << "currFileName.find(\".sdf\"): " << currFileName.find(".sdf") <<
        endl; cout << "condition " << condition << endl; cout << "caseNumber "
        << caseNumber << endl;
  */
      debug = debutStore;
      if (debug) {
        if (condition) {
          cout << "YES:::::: " << caseNumber - 1 << ": " << ObjTitle[caseNumber - 1]
               << " "
               << "FileKey: " << fileKey[caseNumber - 1] << " ";
         // } else {
          //   cout << "NO        " << caseNumber - 1 << ": "
          //       << ObjTitle[caseNumber - 1] << " "
          //       << "FileKey: " << fileKey[caseNumber - 1] << " ";
          cout << endl;
        }
      }
    }
  }
}