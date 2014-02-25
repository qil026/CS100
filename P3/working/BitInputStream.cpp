#include "BitInputStream.hpp"

void BitInputStream::fill(){
	buf = in.get();
	nbits = 7;
}

int BitInputStream::readBit(){
	if(nbits > 7) fill();

	unsigned char result = buf;
	result = result << (7-nbits);
	result = result >> nbits;
	return (int)result;
}