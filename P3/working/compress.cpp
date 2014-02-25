#include <iostream>
#include <iomanip>
#include <fstream>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitOutputStream.hpp"
using namespace std;


int read_input_file(char*,char**);
void create_empty_out_file(char*);

int main(int argc, char** argv){

	if (argc != 3) return 1;

	// Initialize Variables
	int fileSize;
	char* fileContent;
	ofstream fileOut;
	BitOutputStream* out;
	HCTree* huffmanTree;
	vector<int> frequency;

	// Initialize variables
	huffmanTree = new HCTree();
	frequency = vector<int>(256,0);



	// Read input file and store content in fileContent.
	fileSize = read_input_file(argv[1], &fileContent);
	if(fileSize == 0){
		create_empty_out_file(argv[2]);
		return 2;
	}
	if(fileSize < 0) return 3;


	// Get frequency counts
	for(int i = 0; i < fileSize; i++){
		frequency[(int)(fileContent[i])]++;
	}
	// Build huffmanTree
	huffmanTree->build(frequency);
	cout << "Made it through build" << endl;



	// Open output file
	fileOut.open(argv[2], ios::binary);
	if(!fileOut.is_open()) {
		cout << "Output file opening Error!!!" << endl;
		return 4;
	}
	out = new BitOutputStream(fileOut);

	cout << "Opened File" << endl;
	//Write header bits
	huffmanTree->generate_header_bits(*out);

	cout << "Generated header bits" << endl;
	//Use huffman tree to write encoded content
	for(int index = 0; index < fileSize; index++){
		cout << "About to encode " << (unsigned char)fileContent[index] << endl;
		huffmanTree->encode(fileContent[index], *out);
	}	
	out->finalFlush();
	fileOut.close();



	// // Clean up
	// fileOut.close();
	delete [] fileContent;
	delete huffmanTree;
	delete out;

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

void create_empty_out_file(char* name){
	ofstream fout;
	fout.open(name,ios::trunc);
	fout.close();
}