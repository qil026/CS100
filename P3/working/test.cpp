#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <fstream>
// #include "HCTree.hpp"
// #include "HCNode.hpp"

using namespace std;


int main(){

	ofstream fout;
	fout.open("abc",ios::binary);
	fout.put('a');
	fout.put('b');
	fout.put('c');
	fout.flush();
	fout.seekg(0,ios::beg);
	fout.put(' ');

	fout.close();
	return 0;
}