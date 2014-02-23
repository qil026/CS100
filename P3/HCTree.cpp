#include "HCTree.hpp"
#include "HCNode.hpp"
#include <iostream>
using namespace std;


void HCTree::delete_node(HCNode** node){
	if((**node).c0 != 0) delete_node(&((**node).c0));
	if((**node).c1 != 0) delete_node(&((**node).c1));
	delete *node;
}


HCTree::~HCTree(){
	// Clean Up garbage here
	HCNode* node;
	delete_node(&(root));
	delete forest;
}

void HCTree::build(const vector<int>& freqs){
	for(int i = 0; i < freqs.size(); i++){
		if(freqs[i] > 0){
			HCNode* node = new HCNode(freqs[i],(char)i);
			reference[i] = node;
			forest->push(node);
		}
	}
	priority_queue<HCNode*> backup;
	while(forest->size() > 0){
		HCNode* temp = forest->top();
		forest->pop();
		backup.push(temp);
		cout << "Byte: " << (char)temp->symbol << ",  Count: " << temp->count << endl;
	}
	*forest = backup;
	while(forest->size() > 1){
		HCNode* node_1 = forest->top();
		forest->pop();
		HCNode* node_2 = forest->top();
		forest->pop();
		HCNode* parent = new HCNode(0,(char)0,node_1,node_2);
		node_1->p = parent;
		node_2->p = parent;
		node_1->child = 0;
		node_2->child = 1;
		forest->push(parent);
	}
	root = forest->top();
}

void HCTree::print_node_path(HCNode* node, BitOutputStream & out) const{
	if(node->p != root) {
		print_node_path(node->p,out);
	}
	out.writeBit(node->child);
	//std::cout << node->child;
}


void HCTree::encode(byte symbol, BitOutputStream& out) const{
	//std::cout << "\nEncoding character " << (char)symbol << ": ";
	HCNode* node = reference[(int)symbol];
	print_node_path(node, out);
}

int HCTree::decode(BitInputStream& in) const{

}