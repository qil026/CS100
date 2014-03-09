#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "iboggleplayer.h"
#include <vector>
#include <string>
#include <set>
using namespace std;


class BogglePlayer : public IBogglePlayer{
private:
	set<string> *dictionary;
	string** board;
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

	void delete_board();

};

#endif