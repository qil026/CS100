#include <iostream>
#include <fstream>
using namespace std;



int main(int argc, char** argv){

	if (argc != 3) return 1;

	// Initialize Variables
	int fileSize;
	char * inputFile;



	// ----------
	// Read input file into "inputFile" char array
	// Then close the file.
	// Open the given file in binary mode
	ifstream fileIn;
	fileIn.open(argv[1], ios::ate|ios::binary);
	if(!fileIn.is_open()){
		cout << "Error!!" << endl;
		return 2;
	} 

	cout << "Good here" << endl;
	// Get file size first
	fileSize = fileIn.tellg();
	inputFile = new char[fileSize];
	fileIn.seekg(0, ios::beg);

	// Read in the entire file at once
	fileIn.read(inputFile, fileSize);
	fileIn.close();


	cout << inputFile << endl;

	// // Write decoded bytes to the given file 
	// ofstream fileOut;
	// fileOut.open(argv[2], ios::binary);
	// if(!fileOut.is_open()) return 3;
	// // Write to file
	// char * abc = "this is my file";
	// fileOut.write(abc, fileSize);
	// fileOut.close();




	// Clean up
	delete [] inputFile;

	return 0;
}


//---------------------------------------------------------
