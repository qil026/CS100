#include "BitOutputStream.hpp"
#include <iostream>
using namespace std;


void BitOutputStream::flush(){
	out.put((char)(buf.to_ulong()));
	out.flush();
	buf.reset();
	nbits = 7;
}

void BitOutputStream::writeBit(int i){
	if(nbits < 0) flush();

	buf[nbits] = i;
	nbits--;
}

void BitOutputStream::finalFlush(){
	if(nbits != 7) flush();
}