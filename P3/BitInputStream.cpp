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