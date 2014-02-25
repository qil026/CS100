#include <iostream>
#include <fstream>

using namespace std;

void output_byte(char input){
	for(int i = 7; i >= 0; i--){
		unsigned char out = input;
		out <<= (7-i);
		out >>= 7;
		cout << (unsigned int)out;
	}
}

int main(int argc, char** argv){
	
	cout << endl;

	ifstream fin;
	fin.open(argv[1],ios::binary);
	if(!fin.is_open()) return -1;

	char input;
	while(fin.good()){
		input = fin.get();
		output_byte(input);
		cout << endl;
	}

	cout << endl;

	return 0;
}