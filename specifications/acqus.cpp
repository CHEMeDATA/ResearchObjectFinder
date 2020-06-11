
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
/*

./compileList.sh

reset; clang++ acqus.cpp -o acqus.o ; ./acqus.o

*/
bool testLine(string line, string testedString, int whereFistChar = 0)
{
	if ( whereFistChar == 0){
		// search enaywhere in line
	} else {
		// get to the position and search strictly there
	}
	return true;///HERE
}

bool test(string currentFile, string testingName, int location, string what, int whereline = 0, int whereFistChar = 0, string supp = string("") ){
	// file true location
	string line="";///HERE
	if (whereline != 0)
		// get to line of the file to test
		// if (whereFistChar) test anywhere in the line
		testLine(line, testingName, whereFistChar);
		else
		testLine(line, testingName, whereFistChar);

	return true;///HERE
}

int main (){

#include "forCprogInit.txt"

//condition = condition && (   test(currentFile, "", 0, "2D", 2, 21)); 

string currentFile="";///HERE 

//   if(currFileName.compare(".out") == 0) {
string currFileName="";///HERE 
int caseNumber=4;///HERE
bool condition = true;//HERE
#include "forCprog.txt"

if (condition) {
	cout << "true" << endl;
}else{
	cout << "false" << endl;

}
}