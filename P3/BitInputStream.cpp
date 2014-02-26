#include "BitInputStream.hpp"
#include <iostream>
using namespace std;

void BitInputStream::fill(){
	buf = in.get();
	nbits = 7;
}

int BitInputStream::readBit(){
	if(nbits < 0) fill();

	unsigned char result = buf;
	result >>= nbits;
	result &= 0x01;
	nbits--;
	return (int)result;
}

bool BitInputStream::hasMoreBit(){
	// if(nbits >= 0){
	// 	cout << "nbits = " << nbits << " return true" << endl;
	// 	return true;
	// }
	// cout << "nbints = " << nbits;
	// if(in.eof()){
	// 	cout << ",  we've reached end of file. return false." << endl;
	// 	return false;
	// }
	// else {
	// 	cout << ",  we have more bits to read. return true" << endl;
	// 	return true;
	// }
	if(nbits >= 0) return true;
	else{
		unsigned char anything = in.get();
		if(in.eof()) return false;
		else{
			in.putback(anything);
			return true;
		}
	}
}