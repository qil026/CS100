#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"
#include "HCTree.hpp"
using namespace std;

void create_empty_file(char*);

int main(int argc, char** argv){

	if(argc != 3){
		cout << "Incorrect number of arguments. Error!" << endl;
		return 2;
	}

	// Part 1: Open input file and create BitInputStream object
	ifstream fin;
	fin.open(argv[1], ios::binary|ios::ate);
	if(!fin.is_open()){
		cout << "Can't open input file. Error!" << endl;
		return 2;	
	} 
	// Check file size
	unsigned long fileSize = fin.tellg();
	if(fileSize == 0){
		fin.close();
		create_empty_file(argv[2]);
		return 0;
	}
	// Put pointer back to beginning
	fin.seekg(0,ios::beg);
	// Create bit input stream object
	BitInputStream* in = new BitInputStream(fin);


	// Part 2: Rebuild Huffman Code Tree.
	// De-serialize tree structure also record the padding value.
	HCTree* huffman = new HCTree();
	int buildResult = huffman->rebuild(*in);


	// Part 3: Loop through the input file and decode content
	// Open output file first then loop through
	ofstream fout;
	fout.open(argv[2], ios::binary);
	if(!fout.is_open()){
		cout << "Can't open output file. Error!" << endl;
		return 3;
	}
	// Single character case
	if(buildResult != -1){
		unsigned char symbol = (unsigned char)buildResult;
		unsigned int length = huffman->get_single_char_length(*in);
		for(unsigned int i = 0; i < length; i++){
			fout.put(symbol);
		}
	}
	else{
		while(in->hasMoreBit()){
			int outChar = huffman->decode(*in);
			fout.put((unsigned char)outChar);
			//cout << "Looping through bits, i=" << i++;
			//cout << ",  " << (char)outChar << endl;
		}	
	}
	

	// Part 4: Clean up.
	fin.close();
	fout.close();
	delete huffman;
	delete in;

	return 0;
}


void create_empty_file(char* file){
	ofstream fout;
	fout.open(file, ios::binary);
	fout.close();
}