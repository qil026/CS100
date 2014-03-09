#include "boggleplayer.h"
#include <iostream>
#include <set>
#include <vector>
using namespace std;


BogglePlayer::BogglePlayer(){
	dictionary = new set<string>();
	lexiconBuilt = false;
	boardBuilt = false;
}

BogglePlayer::~BogglePlayer(){
	delete dictionary;

	delete_board();
}


// Useless method if called before setBoard (unfortunately this is the case)
// So simply copy all the given word to the lexicon set, deal with it later
void BogglePlayer::buildLexicon(const vector<string>& word_list){
	vector<string>::const_iterator it;
	for(it = word_list.begin(); it != word_list.end(); it++){
		dictionary->insert(*it);
	}
	list = &word_list;
	lexiconBuilt = true;
}


void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
	// Populate board.
	set<string> validChar;
	board = new *string[rows];
	for(int i = 0; i < rows; i++){
		board[i] = new string[cols];
		for(int k = 0; k < cols; k++){
			board[i][k] = diceArray[i][k];
			validChar.insert(board[i][k]);
		}
	}

	vector<string>::iterator it;
	for(it = dictionary->begin(); it != dictionary->end(); it++){
		string word = *it;
		for(int i = 0; i < word.length(); i++){
			if(!(dictionary))
		}
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
	//return (completeDictionary->find(word_to_check) != completeDictionary->end());
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






