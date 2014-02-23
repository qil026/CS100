#include "BitOutputStream.hpp"
#include <iostream>

void BitOutputStream::flush(){
	out.put((char)(buf.to_ulong()));
	//std::cout << (char)buf.to_ulong() << std::endl;
	out.flush();
	buf.reset();
	nbits = 7;
}

void BitOutputStream::writeBit(int i){
	if(nbits < 0) flush();

	buf[nbits] = i;
	nbits--;
}