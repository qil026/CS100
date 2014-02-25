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





	// Part 4: Clean up.
	fin.close();
	delete huffman;



	return 0;
}