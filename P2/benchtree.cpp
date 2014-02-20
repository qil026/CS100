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

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  
 *  Name:  Qingyang Liu
 *  Login: qil026
 *  Preferred Name: Frankie Liu
 *
 */



void print_info(string, string, const int, const int);
void populate_tree(void*,vector<countint>*,string,bool,const int);
void search_tree(void*,vector<countint>*,string);
void print_stat(vector<double>*,int);




int main(int argc, char** argv){

	//Check the number of command line parameters.
	if(argc != 5){
		cout << "Incorrect number of parameters! ERROR." << endl;
		return 1;
	}

	// Store command line arguments.
	string type = argv[1];
	string sequence = argv[2];
	int const maxSize = atoi(argv[3]);
	int const repeat = atoi(argv[4]);
	bool shuffled = (sequence == "shuffled") ? true : false;
		
	// Print test information header
	print_info(type, sequence, maxSize, repeat);


	// Initialize our target.
	// Here we declare tree using void* so that later
	// We can cast it to any type determined at run time.
	void* tree;
	if(type == "bst") tree = new BST<countint>();
	else if(type == "rst") tree = new RST<countint>();
	else if(type == "set") tree = new set<countint>();
	else{
		cout << "Wrong structure type. ERROR!" << endl;
		return -1;
	}
	vector<countint>* list = new vector<countint>();
	vector<double> data;
	
	// Start Test!!
	for(int N = 1; N < maxSize; N=N*2+1){
		// Simulate multiple runs for each data size N
		// Get ready to collect data, empty the data vector first
		data.clear();
		for(int r = 0; r < repeat; r++){
			// First populate tree
			populate_tree(tree,list,type,shuffled,N);
			countint::clearcount();
			search_tree(tree,list,type);
			double average = countint::getcount() / (double)N;
			data.push_back(average);	
		}
		print_stat(&data,N);
	}
	
	if(type=="rst") delete((RST<countint>*)tree);
	else if(type=="bst") delete((BST<countint>*)tree);
	else delete((set<countint>*)tree);

	delete(list);

	return 0;
}




// Functions to help implement main logic
// --------------------------------------

void search_tree(void* tree, vector<countint>* list, string type){
	vector<countint>::iterator it;
	if(type == "rst"){
		for(it = list->begin(); it != list->end(); it++){
			((RST<countint>*)tree)->find(*it);
		}
	}
	else if (type == "bst"){
		for(it = list->begin(); it != list->end(); it++){
			((BST<countint>*)tree)->find(*it);
		}
	}
	else{
		for(it = list->begin(); it != list->end(); it++){
			((set<countint>*)tree)->find(*it);
		}
	}
}


// Criterions of algorithm:
// list needs to be empty
// after insertion, list has to have size N 
// tree needs to be empty
// after insertion, tree has to have size N
void populate_tree(void* tree, vector<countint>* list, string type,bool shuffled, const int N){
	vector<countint>::iterator it;
	list->clear();

	for(int i = 0; i < N; i++){
		list->push_back(i);
	}
		
	if(shuffled) random_shuffle(list->begin(),list->end());

	if(type == "rst"){
		((RST<countint>*)tree)->clear();
		for(it = list->begin(); it != list->end(); it++)
			((RST<countint>*)tree)->insert(*it);
	} 
	else if (type == "bst"){
		((BST<countint>*)tree)->clear();
		for(it = list->begin(); it != list->end(); it++)
			((BST<countint>*)tree)->insert(*it);
	}
	else{
		((set<countint>*)tree)->clear();
		for(it = list->begin(); it != list->end(); it++)
			((set<countint>*)tree)->insert(*it);
	}
}


void print_info(string type, string sequence, const int maxSize, const int repeat){
	cout << "# Benchmarking average number of comparisons for successful find" << endl;
	cout << "# Data structure: " << type << endl;
	cout << "# Data: " << sequence << endl;
	cout << "# N is powers of 2, minus 1, from 1 to " << maxSize << endl;
	cout << "# Averaging over " << repeat << " runs for each N" << endl;
	cout << "# " << endl;
	// Print header for data
	cout << setw(10) << "# N   ";
	cout << "\t" << setw(10) << "avg comps";
	cout << "\t" << setw(10) << "stdev  " << endl;
}


void print_stat(vector<double>* data, int N){
	double regTotal = 0;
	double sqTotal = 0;

	vector<double>::iterator it;
	for(it = data->begin(); it != data->end(); it++){
		regTotal += *it;
		sqTotal += (*it) * (*it);
	}

	double regAvg = regTotal / (double)data->size();
	double sqAvg = sqTotal / (double)data->size();
	double stdev = sqAvg - (regAvg * regAvg);
	if (stdev < 1e-16) stdev = 0;
	else stdev = sqrt(stdev);

	cout << setw(10) << N;
	cout << "\t" << setw(10) << regAvg;
	cout << "\t" << setw(10) << stdev << endl;
}