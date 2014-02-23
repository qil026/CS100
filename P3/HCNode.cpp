#include "HCNode.hpp"
#include <iostream>
using namespace std;

bool HCNode::operator<(const HCNode& other){
	return (this->count > other.count);
}

bool comp(HCNode* one, HCNode* other){
	return (one < other);
}

void HCNode::display(){
	this->c0->display();
	this->c1->display();
	cout <<"Count: " << this->count << ",  ";
	cout << "Address: " << this << ",  left: " << this->c0 << ",  right: " << this->c1 << endl;
}
