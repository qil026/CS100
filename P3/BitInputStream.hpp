#ifndef BITINPUTSTREAM
#define BITINPUTSTREAM
#include <fstream>

class BitInputStream{
private:
	unsigned char buf;
	int nbits;
	std::ifstream & in;
	
public:
	BitInputStream(std::ifstream & in):in(in){
		buf = 0;
		nbits = -1;
	}

	void fill();

	int readBit();

	bool hasMoreBit();
};

#endif