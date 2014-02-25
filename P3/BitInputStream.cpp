#include "BitInputStream.hpp"

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