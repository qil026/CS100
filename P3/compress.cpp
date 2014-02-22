#include <iostream>
#include <fstream>
using namespace std;


int read_input_file(char*,char**);
int write_output_file(char*,char*,int);

int main(int argc, char** argv){

	if (argc != 3) return 1;

	// Initialize Variables
	int fileSize;
	int byteWritten;
	char* fileContent;


	// Read input file and store content in fileContent.
	fileSize = read_input_file(argv[1], &fileContent);
	//if(fileSize < 0) return -1;

	// Compress the content using Huffman Coding Tree


	// Write the compressed content to output file
	byteWritten = write_output_file(argv[2],fileContent,fileSize);
	if(byteWritten < 0) return -1;

	cout << fileSize << " bytes written to file: " << argv[2] << endl;

	// Clean up
	delete [] fileContent;

	return 0;
}


//---------------------------------------------------------

// Parameter 1: input file name 					char array
// Parameter 2: memory address to store content 	address of char array
int read_input_file(char * fileName, char ** content){
	ifstream fileIn;
	fileIn.open(fileName, ios::ate|ios::binary);
	if(!fileIn.is_open()){
		cout << "Input file opening Error!!" << endl;
		delete [] content;
		return -1;
	} 
	// Get file size first
	int fileSize = fileIn.tellg();
	*content = new char[fileSize];
	fileIn.seekg(0, ios::beg);
	// Read in the entire file at once
	fileIn.read(*content, fileSize);
	fileIn.close();
	return fileSize;
}

// Parameter 1: output file name 		char array
// Parameter 2: the content to write	char array
// Parameter 3: the size of content 	int
int write_output_file(char* fileName, char* content, int fileSize){
	// Write decoded bytes to the given file 
	ofstream fileOut;
	fileOut.open(fileName, ios::binary);
	if(!fileOut.is_open()) {
		cout << "Output file opening Error!!!" << endl;
		delete [] content;
		return -1;
	}
	// Write to file
	fileOut.write(content, fileSize);
	fileOut.close();
	return fileSize;
}