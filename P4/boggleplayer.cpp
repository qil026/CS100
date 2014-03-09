#include "boggleplayer.h"
#include <iostream>
using namespace std;


BogglePlayer::BogglePlayer(){
	lexicon = new set<string>();
	lexiconBuilt = false;
	boardBuilt = false;
}

BogglePlayer::~BogglePlayer(){
	delete lexicon;

	delete_board();
}


// Useless method if called before setBoard (unfortunately this is the case)
// So simply copy all the given word to the lexicon set, deal with it later
void BogglePlayer::buildLexicon(const vector<string>& word_list){
	vector<string>::const_iterator it;
	for(it = word_list.begin(); it != word_list.end(); it++){
		lexicon->insert(*it);
	}
	//cout << "Frankie: lexicon is built...." << endl;
	list = &word_list;
	lexiconBuilt = true;
}


void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
	
	board = new *string[rows];
	for(int i = 0; i < rows; i++){
		board[i] = new string[cols];
	}


	// for(int i = 0; i < rows; i++){
	// 	string *row = new string[cols];
	// 	for(int k = 0; k < cols; k++){
	// 		string word = diceArray[i][k];
	// 		row[k] = word;
	// 	}
	// 	board->push_back(row);
	// }
	cout << "Frankie: board is built" << endl;
	boardBuilt = true;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){
	// If either or both lexicon and board are not built, return false
	if(!(lexiconBuilt && boardBuilt)) return false;

	//
	words->insert("lol");
	words->insert("Stupid");
	cout << "Frankie: getting all valid words" << endl;
	return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check){
	cout << "Frankie: isInLexicon is called." << endl;
	//return (lexicon->find(word_to_check) != lexicon->end());
	return true;
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
	vector<int> result;
	cout << "Frankie: isOnBoard is called" << endl;
	return result;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){

}

void BogglePlayer::delete_board(){

	delete [] board;
}

