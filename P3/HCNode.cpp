#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other){
	return (this->count > other.count);
}


bool comp(HCNode* one, HCNode* other){
	return (one < other);
}