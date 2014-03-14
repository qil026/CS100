#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "iboggleplayer.h"
#include "boggleutil.h"
#include <vector>
#include <string>
#include <set>
using namespace std;


class BogglePlayer : public IBogglePlayer{
private:
	WordTree *dictionary;

	BoardNode*** board;
	int boardRows,boardCols;


	
	bool lexiconBuilt;
	bool boardBuilt;

public:
	BogglePlayer();
	void buildLexicon(const vector<string>& );
	void setBoard(unsigned int , unsigned int , string** );
	bool getAllValidWords(unsigned int , set<string>* );
	bool isInLexicon(const string& );
	vector<int> isOnBoard(const string& );
	void getCustomBoard(string** &, unsigned int *, unsigned int *);
	~BogglePlayer();

	// Added helper functions
	void buildNeighbors(BoardNode*,set<int>,WordNode*);
};

#endif