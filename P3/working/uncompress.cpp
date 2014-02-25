#include <iostream>
#include <fstream>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv){

	if(argc != 3){
		cout << "Incorrect number of arguments. Error!" << endl;
		return 1;
	}



	// Initialize Variables
	HCTree* huffmanTree = new HCTree();
	ifstream fin;
	BitInputStream *input;

	// Open input file
	fin.open(argv[1], ios::binary);
	if(!fin.is_open()){
		cout << "Can't open file to read. Error!" << endl;
		return 2;
	}
	input = new BitInputStream(fin);

	// Read input file
	huffmanTree->retrieve_tree_structure(input);





	
	// Delete Resources
	delete huffmanTree;
	delete input;

	return 0;
}