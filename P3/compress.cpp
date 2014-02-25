#include "BitOutputStream.hpp"
#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void get_input_file_byte_frequency(char* file, vector<int>* frequency);

int main(int argc, char** argv){

	if(argc != 3){
		cout << "Incorrect number of args. Error" << endl;
		return 1;
	}

	// Part 1: Open input file to read
	// Fill out frequency array.
	unsigned long fileSize;
	vector<int>* frequency = new vector<int>(256, 0l);
	ifstream fin;
	// Get file size by placing read pointer at the end
	fin.open(argv[1], ios::binary | ios::ate);
	fileSize = fin.tellg();
	// Put pointer back to beginning
	fin.seekg(0,ios::beg);
	// loop through file to populate frequency vector
	for(long i = 0; i < fileSize; i++){
		unsigned char value = fin.get();
		unsigned int index = (unsigned int) value;
		(*frequency)[index]++;
	}
	// Put pointer back for later processing
	fin.seekg(0,ios::beg);
	

	// Part 2: Create Huffman Coding Tree object, then provide
	// the frequency vector to build the actual tree.
	HCTree* huffman = new HCTree();
	huffman->build(*frequency);

	// Part 3: Write to output file
	// First generate header bits and write to given file
	// Then calculate and write padding bit info
	// Finally write the encoded body to file
	// step 0, open output file and create bitoutputstream object.
	ofstream fout;
	fout.open(argv[2], ios::binary);
	if(!fout.is_open()){
		cout << "Couldn't open output file to write. Error!" << endl;
		return 2;
	}
	BitOutputStream* out = new BitOutputStream(fout);
	// step 1, write header bits into file (including padding info)
	huffman->generate_header_bits(*out);
	// step 2, write encoded content into output file
	// loop through input content and encode each byte
	for(int i = 0; i < fileSize; i++){
		unsigned char byte = fin.get();
		huffman->encode(byte, *out);
	}
	out->finalFlush();


	// Part 4: Clean up variables
	fin.close();
	fout.close();
	delete frequency;
	delete huffman;
	delete out;

	return 0;
}


// Read input file byte by byte, for each byte, use it as the index to
// frequency vecotr, then add one the corresponding element.
// No return needed
void get_input_file_byte_frequency(char* file, vector<int>* frequency){
	
}