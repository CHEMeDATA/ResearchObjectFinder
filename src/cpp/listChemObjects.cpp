
#include <math.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*

# takes the excel sheet with tab sepration and makes code to insert in cpp
program
specifications/compileList.sh
# extracts only the part of the zip file necessary for identification of objects

cd data
../src/bash/unzipRelevant.bash
cd ..

cd src/cpp
clang++ listChemObjects.cpp -o listChemObjects.o 
cd ../..

src/cpp/listChemObjects.o data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt "" unziped/
src/cpp/listChemObjects.o data/prepareYaretaFolderNasca_phyto.zip_listFiles.txt "" unziped/
src/cpp/listChemObjects.o data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt "" unziped/ > examples/demo_archive_yareta.json


*/

bool hasEnding(const string &fullString, const string &ending) {
  // test if the string fullString ends with the string endsing
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare(fullString.length() - ending.length(),
                                    ending.length(), ending));
  } else {
    return false;
  }
}

inline bool testLine(const string &line, const string &testedString,
                     const int &whereFistChar) {
  // Test the presence of the string testedString int the string line. Option:
  // indicate where to look using the int whereFistChar
  if (whereFistChar == 0) {
    return (line.find(testedString) != std::string::npos);
  } else {
    //  cout << " out of this... :  " << line << endl;
    // cout << " looked only there <"
    //     << line.substr(whereFistChar - 1, testedString.length()) << ">"
    //    << endl;
    // cout << " out of this cut ...testedString :  " << testedString << endl;

    return (line.substr(whereFistChar - 1, testedString.length())
                .find(testedString) != std::string::npos);
  }
}

bool test(const string &currentFile, const string &testingName,
          const int &location, string what = string(""), int whereline = 0,
          int whereFistChar = 0, string supp = string("")) {
  /*
  std::cout << "-------------------------------------- " << '\n';
  std::cout << " testing : " << currentFile ;
  std::cout << " what : <" << what << ">";
  std::cout << " whereline : " << whereline ;
  std::cout << " whereFistChar : " << whereFistChar ;
  std::cout << " testingName : " << testingName ;
  std::cout << " location : " << location << endl;
  */

  // file location (manage const int &location)
  string folderSeparator = "/";
  std::size_t foundSep = currentFile.find_last_of(folderSeparator);
  string fn = currentFile.substr(foundSep + 1);
  string workPath = currentFile.substr(0, foundSep);
  for (int index = 0; index < location; index++) {
    foundSep = workPath.find_last_of(folderSeparator);
    workPath = workPath.substr(0, foundSep);
    // std::cout << "<path: " << workPath << '\n';
  }
  workPath.append(folderSeparator);
  workPath.append(testingName);

  // std::cout << "_path: " << workPath << '\n';

  ifstream fileStream;
  bool found;
  string line = "";

  // attemps to open...
  fileStream.open(workPath);
  if (!fileStream.is_open()) {  // file does not exist
    return false;
  }
  if (what.empty()) {  // file exists and this is all that is required
    return true;
  }

  // OK open, search for something...
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
  // std::cout << "First tested line : " << line << '\n';

  // testing ...
  found = testLine(line, what, whereFistChar);
  if (found) {
    // std::cout << "found : " << what << '\n';
    return true;
  }
  if (whereline > 0) {  // if only one line is tested
    return false;
  }

  for (int i = 0; true; i++) {
    if (!getline(fileStream, line)) {
      fileStream.close();
      return false;
    }
    found = testLine(line, what, whereFistChar);
    if (found) {
      // std::cout << "found :" << what << '\n';
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv) {
  bool firstLine = true;
// The forCprogInit.txt file contains a list of vectors describing each object 
// Example:
//vector<string> ObjTitle; // initialize the ObjTitle vector of string
//ObjTitle.push_back("Gaussian file"); // fill the vector with data
// ...
#include "../../specifications/forCprogInit.txt"
  ifstream mainfileStream;

  int bestCaseNumber;
  double bestCaseValue;
  bool condition;
  bool condition2;
  int addme;
  int caseNumber;
  bool debug = true;
  debug = false;  ////////// DEBUG
  bool debutStore;
  string line;
  string currFileName;
  string rootPathReplaceFrom, rootPathReplaceTo;
  bool replaceRootPath;
  // string currentFile;
  /* class Data {
   public:
    std::vector<double> x;
    std::vector<double> y;
  };
  Data data;   data.x.clear();
    data.y.clear();
*/
  if (argc < 2) {
    cerr << argv[0] << ": missing input file. Usage: " <<  argv[0] << " infile [path1 path2]" << endl;
    cerr << " (Where infile includes the list of file to analye and path1 and path2 are the respectively the part of he path for files found in infile to remove and add respectivley.)" << endl;
    return -1;
  }

  mainfileStream.open(argv[1]);
  if (!mainfileStream.is_open()) {  // file does not exist
    cerr << argv[0] << ": " << argv[1] << " : no such file or directory"
         << endl;
    return -1;
  }
  // change path from original location in zip file to true location
  if (argc > 3) {
    rootPathReplaceFrom.assign(argv[2]);
    rootPathReplaceTo.assign(argv[3]);
    replaceRootPath = true;
  } else {
    replaceRootPath = false;
  }

  // for (int loop = 1; loop < argc; loop++) {
  while (getline(mainfileStream, line)) {
    bestCaseValue = 0.0;
    bestCaseNumber = -1;
    // currentFile.clear();
    // currentFile.assign(argv[loop]);
    currFileName.clear();
    currFileName.assign(line);
    if (replaceRootPath) {
      //    cout << "before " << currFileName << endl;
      if (rootPathReplaceFrom.length() > 0)
        currFileName = currFileName.substr(rootPathReplaceFrom.length());
      if (rootPathReplaceTo.length() > 0)
        currFileName.insert(0, rootPathReplaceTo);
      //           cout << "after " << currFileName  << endl;
    }
    if (debug) {
      // cout << "========================================================="
      //      << endl;
      cout << "Work on file: " << currFileName;
      cout << endl;
    }
    for (caseNumber = 1; caseNumber <= 32; caseNumber++) {
      condition = true;
      condition2 = false;

      // Prepare long list of test in forCprog.txt file...
      debutStore = debug;
      debug = false;
      // if (loop == 1) debug = false;  // was true
      // std::cout << "++testing : " << currentFile << '\n';
      // std::cout << "++testingName : " << currFileName << '\n';

// The forCprog.txt returns bools for condition and condition2 depending on
// currFileName and caseNumber
#include "../../specifications/forCprog.txt"

      //  cout << "condition  " << condition << ": " << endl;
      //   cout << "condition2 " << condition2 << ": " << endl;

      condition = condition && condition2;

      /*
        cout << "currFileName: " << currFileName << endl;
        cout << "currFileName.find(\".sdf\"): " << currFileName.find(".sdf") <<
        endl; cout << "condition " << condition << endl; cout << "caseNumber "
        << caseNumber << endl;
      */
      if ((Level[caseNumber - 1] > bestCaseValue) && condition) {
        bestCaseValue = Level[caseNumber - 1];
        bestCaseNumber = caseNumber;
      }
      debug = debutStore;

      if (debug && condition2) {
        if (condition) {
          cout << "YES:::::: " << caseNumber << ": "
               << ObjTitle[caseNumber - 1];
          //<< " "
          //<< "FileKey: " << fileKey[caseNumber - 1] << " "
          //<< "Level: " << Level[caseNumber - 1] << " ";
        } else {
          cout << "NO        " << caseNumber << ": ";
          //       << ObjTitle[caseNumber ] << " "
          //       << "FileKey: " << fileKey[caseNumber - 1] << " ";
        }
        cout << endl;
      }
    }
    caseNumber = bestCaseNumber;
    // json output
    if (caseNumber > 0) {
      if (firstLine) {
        cout << "[" << endl;
        firstLine = false;
      } else {
        cout << "," << endl;
      }
      cout << " {" << endl
           << "  \"objTitle\":\"" << ObjTitle[caseNumber - 1] << "\"" << "," << endl
           << "  \"basicCategory\":\"" << BasicCathegory[caseNumber - 1] << "\"" << "," << endl
           << "  \"type\":\"" << Type[caseNumber - 1] << "\"" << "," << endl
           << "  \"subType\":\"" << SubType[caseNumber - 1] << "\"" << "," << endl
           << "  \"fileKey\": \"" << fileKey[caseNumber - 1] << "\"" << "," << endl
           << "  \"level\": " << Level[caseNumber - 1] << "," << endl
           << "  \"file\":\"" << line << "\"" << endl // no comma, this is the last...
           << " }"  ;// no end of line, will depend if need a comma...
    }
  }
  cout << endl << "]" << endl;
}