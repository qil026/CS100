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
	int count = 0;
	priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp>* backup = new priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp >();
	for(int i = 0; i < freqs.size(); i++){
		if(freqs[i] > 0){
			HCNode* node = new HCNode(freqs[i],(char)i);
			reference[i] = node;
			forest->push(node);
			backup->push(node);
			count++;
		}
	}
	cout << "Forest size: " << forest->size() << ", compare to count: " << count << endl;
	while(backup->size() > 0){
		HCNode * node = backup->top();
		backup->pop();
		cout << (char)node->symbol << ": " << node->count << endl;
	}
	int i = 0;
	while(forest->size() > 1){
		HCNode* node_1 = forest->top();
		forest->pop();
		HCNode* node_2 = forest->top();
		cout << "Round " << i++;
		cout << "    Node popped is: (" << (char)node_1->symbol << ", " << node_1->count << ") and (";
		cout << (char)node_2->symbol << ", " << node_2->count << ") " << endl;
		forest->pop();
		HCNode* parent = new HCNode(
			node_1->count + node_2->count,(char)0,node_1,node_2);
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
	cout << node->child;
}


void HCTree::encode(byte symbol, BitOutputStream& out) const{
	//std::cout << "\nEncoding character " << (char)symbol << ": ";
	HCNode* node = reference[(int)symbol];
	if(node != root)
		print_node_path(node, out);
	//cout << "Im exiting encode." << endl;
}

int HCTree::decode(BitInputStream& in) const{

}


void HCTree::generate_header_bits(BitOutputStream & out) const{
 
}