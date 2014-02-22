#include <iostream>

using namespace std;


int main(){

	int myInt = -345345;
	unsigned int myUint = myInt;

	cout << myUint << endl;

	char abc = 'a';

	myUint = abc;
	myInt = abc;

	cout << "Un int: " << myUint << ",  int: " << myInt << endl;

	return 0;
}