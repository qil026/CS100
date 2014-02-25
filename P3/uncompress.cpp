#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"
#include "HCTree.hpp"
using namespace std;


int main(int argc, char** argv){

	if(argc != 3){
		cout << "Incorrect number of arguments. Error!" << endl;
		return 2;
	}

	// Part 1: Open input file and create BitInputStream object
	ifstream fin;
	fin.open(argv[1], ios::binary);
	if(!fin.is_open()){
		cout << "Can't open input file. Error!" << endl;
		return 2;	
	} 
	BitInputStream* in = new BitInputStream(fin);

	// Part 2: Rebuild Huffman Code Tree.
	// De-serialize tree structure also record the padding value.
	HCTree* huffman = new HCTree();
	huffman->rebuild(*in);

	cout << "Made it through build" << endl;
	// Part 3: Loop through the input file and decode content
	// Open output file first then loop through
	ofstream fout;
	fout.open(argv[2], ios::binary);
	if(!fout.is_open()){
		cout << "Can't opening output file. Error!" << endl;
		return 3;
	}

	while(in->hasMoreBit()){
		int outChar = huffman->decode(*in);
		fout.put((unsigned char)outChar);
		//cout << "Looping through bits, i=" << i++;
		//cout << ",  " << (char)outChar << endl;
	}


	// Part 4: Clean up.
	fin.close();
	fout.close();
	delete huffman;



	return 0;
}