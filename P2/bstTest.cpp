#include <set>
#include <vector>
#include <math.h>
#include <string>
#include <utility>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "BST.hpp"
#include "RST.hpp"
#include "countint.hpp"

using namespace std;


void print_info(string, string, const int, const int);
void populate_tree(void*,vector<countint>*,string,bool,const int);
void search_tree(void*,vector<countint>*,string);
void print_stat(vector<double>*,int);




int main(int argc, char** argv){


	BST<countint>* tree = new BST<countint>();

	for(int i = 32; i > 0; i--)
		tree->insert(i);

	countint::clearcount();

	int total = 0;
	for(int i = 0; i < 32; i++){
		tree->find(i);
		int temp = countint::getcount() - total;
		cout << "count is: " << temp << endl;
		total += temp;
	}
	cout << "Total count is: " << countint::getcount() << endl;
	cout << "Average count: " << countint::getcount() / (double)32 << endl;

	delete(tree);
	return 0;
}