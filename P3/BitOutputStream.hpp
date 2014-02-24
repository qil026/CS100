#ifndef BITOUTPUTSTREAM
#define BITOUTPUTSTREAM

#include <fstream>
#include <bitset>

class BitOutputStream{
private:
	std::bitset<8> buf;
	int nbits;
	std::ofstream & out;

public:
	BitOutputStream(std::ofstream & os):out(os){
		buf.reset();
		nbits = 7;
	}

	void flush();

	void writeBit(int i );

	void finalFlush();

};

#endif