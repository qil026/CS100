#include <set>
#include <vector>
#include <math.h>
#include <utility>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "BST.hpp"
#include "RST.hpp"
#include "countint.hpp"

using namespace std;

void clean_up(RST<countint>* rst, BST<countint>* bst, set<countint>* red);
void print_info(const char* dataStructure, const char* sequence, const int maxSize, const int repeat);
void print_stat(vector<double> list, int size);
pair<double,double> calculate_stdev(vector<double> list);

int main(int argc, char** argv){

	// Check the number of command line parameters.
	if(argc != 5){
		cout << "Incorrect number of parameters! ERROR." << endl;
		return 1;
	}

	// Store command line arguments.
	char const * dataStructure = argv[1];
	char const * sequence = argv[2];
	int const maxSize = atoi(argv[3]);
	int const repeat = atoi(argv[4]);


	// Start Test
	print_info(dataStructure, sequence, maxSize, repeat);

	// Create data containers
	vector<double> comparison;
	vector<countint> list;

	// Declare pointers for each data structure
	RST<countint>* rst = new RST<countint>();
	BST<countint>* bst = new BST<countint>();
	set<countint>* red = new set<countint>();
	// Set appropriate shuffling flag.
	bool shuffled = (strcmp(sequence,"shuffled")) ? true : false;

	// Begin Test, for each size of tree:
	// first repeat the specified amount of time,
	// then collect data and continue to the next.
	for(int N = 1; N <= maxSize; N=N*2+1){
		comparison.clear();
		for(int r = 0; r < repeat; r++){
			// populate items in tree
			for(int i = 0; i < N; i++)
				list.push_back(i);
			if(shuffled)
				random_shuffle(list.begin(), list.end());
			vector<countint>::iterator it = list.begin();
			vector<countint>::iterator end = list.end();
			
			if(strcmp(dataStructure,"rst")){
				rst->clear();
				for(; it != end; it++) rst->insert(*it);
				countint::clearcount();
				for(it = list.begin(); it != end; it++) rst->find(*it);
			}
			else if(strcmp(dataStructure,"bst")){
				bst->clear();
				for(; it != end; it++) bst->insert(*it);
				countint::clearcount();
				for(it = list.begin(); it != end; it++) bst->find(*it);

			}
			else if(strcmp(dataStructure,"set")){
				red->clear();
				for(; it != end; it++) red->insert(*it);
				countint::clearcount();
				for(it = list.begin(); it != end; it++) red->find(*it);
			}
			else{
				cout << "ERROR on input parameter argv[1]!" << endl;
				return 1;
			}

			// Calculate the average comparison in 1 tree then add to list
			double avgcmp = countint::getcount() / (double)N;
			comparison.push_back(avgcmp);
		}
		print_stat(comparison,N);
	}



	return 0;
}


void print_info(const char* dataStructure, const char* sequence, const int maxSize, const int repeat){
	cout << "# Benchmarking average number of comparisons for successful find" << endl;
	cout << "# Data structure: " << dataStructure << endl;
	cout << "# Data: " << sequence << endl;
	cout << "# N is powers of 2, minus 1, from 1 to " << maxSize << endl;
	cout << "# Averaging over " << repeat << " runs for each N" << endl;
	cout << "# " << endl;
	// Print header for data
	cout << setw(10) << "# N   ";
	cout << "\t" << setw(10) << "avg comps";
	cout << "\t" << setw(10) << "stdev  " << endl;
}

void print_stat(vector<double> list, int size){
	pair<double,double> result = calculate_stdev(list);

	cout << setw(10) << size;
	cout << "\t";
	cout << setw(10) << result.first;
	cout << "\t";
	cout << setw(10) << result.second;
	cout << endl;
}

pair<double,double> calculate_stdev(vector<double> list){
	// First find the Sums
	double regTotal = 0;
	double sqTotal = 0;
	vector<double>::iterator it = list.begin();
	vector<double>::iterator end = list.end();
	for(; it != end; it++){
		regTotal += *it;
		sqTotal += (*it) * (*it);
	}

	// Now calculate the averages standard deviation
	double regAvg = regTotal / (double)(list.size());
	double sqAvg = sqTotal / (double)(list.size());
	double stdev = sqAvg - (regAvg * regAvg);
	stdev = sqrt(stdev);

	return pair<double,double>(regAvg, stdev);
}
