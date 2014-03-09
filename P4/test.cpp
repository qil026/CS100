#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main(){
	int size = 23;
	string* word = new string[size];

	delete word;
	return 0;
}