#ifndef BITINPUTSTREAM
#define BITINPUTSTREAM
#include <fstream>

class BitInputStream{
private:
	unsigned char buf;
	int nbits;
	bool untouched;
	std::ifstream & in;
	
public:
	BitInputStream(std::ifstream & in):in(in){
		buf = 0;
		nbits = -1;
		untouched = true;
	}

	void fill();

	int readBit();

	bool hasMoreBit();

	bool endOfFile();
};

#endif