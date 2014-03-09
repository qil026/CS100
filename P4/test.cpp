#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main(){
	set<string> invalidChar;
	char c[2] = 'a';
	string s = to_string(c);
	invalidChar.insert(s);
	invalidChar.insert("asdsdff");
	invalidChar.insert("11");
	invalidChar.insert("oij");

	set<string>::iterator it;
	for(it=invalidChar.begin();it!=invalidChar.end();it++){
		cout << (string)*it << endl;
	}

	// for(int i = 'a'; i <= 'q'; i++){
	// 	string character = to_string(i);
	// 	invalidChar.insert(character);
	// 	//cout << character << endl;
	// }
	// invalidChar.insert("qu");
	// set<string>::iterator it;
	// for(it=invalidChar.begin();it!=invalidChar.end();it++){
	// 	cout << (string)*it << endl;
	// }
	return 0;
}