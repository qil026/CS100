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
	for(int i = 0; i < freqs.size(); i++){
		if(freqs[i] > 0){
			HCNode* node = new HCNode(freqs[i],(char)i);
			leaves[i] = node;
			forest->push(node);
			count++;
		}
	}
	int i = 0;
	while(forest->size() > 1){
		HCNode* node_1 = forest->top();
		forest->pop();
		HCNode* node_2 = forest->top();
		// cout << "Round " << i++;
		// cout << "    Node popped is: (" << (char)node_1->symbol << ", " << node_1->count << ") and (";
		// cout << (char)node_2->symbol << ", " << node_2->count << ") " << endl;
		forest->pop();
		HCNode* parent = new HCNode(
			node_1->count + node_2->count,(char)0xFF,node_1,node_2);
		parent->child = -1;
		node_1->p = parent;
		node_2->p = parent;
		node_1->child = 0;
		node_2->child = 1;
		forest->push(parent);
	}
	root = forest->top();

	for(int i = 0; i < leaves.size(); i++){
		cout << "i: " << i << ",  ";
		if(leaves[i] == 0) cout << "0" << endl;
		else cout << "1" << endl;
	}
}

void HCTree::encode(byte symbol, BitOutputStream& out) const{
	//std::cout << "\nEncoding character " << (char)symbol << ": ";
	//cout << "Before accessing leaves" << endl;
	HCNode* node = leaves[(unsigned int)symbol];
	//cout << "After accessing leaves" << endl;
	if(node != root)
		print_node_path(node, out);
	//cout << "Im exiting encode." << endl;
}

int HCTree::decode(BitInputStream& in) const{

}

void HCTree::generate_header_bits(BitOutputStream & out){
	serialize_tree();
	unsigned long bitsWritten =  write_tree_structure(out);
	write_padding_bit(bitsWritten, out);
}

void HCTree::retrieve_tree_structure(BitInputStream& in){
	int count = 0; 		// number of child nodes in the tree.
	// Read the input stream to re construct the tree.
	// If the first bit is 1, then it is a leaf, the entire file has 
	// only one char type
	int firstBit = in.readBit();
	if(firstBit == 1){
		unsigned char symbol = 0;
		for(int i = 7; i >= 0; i--){
			unsigned char bit = in.readBit();
			bit = bit << i;
			symbol = symbol | bit;
		}
		root = new HCNode(0,symbol,0,0);
	}
	// If the first bit is 0, it is an internal node, and we can proceed.
	else{


	}


}

// Private Helper Function Implementations
// ---------------------------------------
void HCTree::print_node_path(HCNode* node, BitOutputStream & out) const{
	if(node->p != root) {
		print_node_path(node->p,out);
	}
	out.writeBit(node->child);
	//cout << node->child;
}

void HCTree::serialize_tree(){
	int height = calculate_tree_height(root);

	for (int i = 1; i <= height; i++){
		serialize_tree_level(root,i);
	}
}

int HCTree::calculate_tree_height(HCNode* node){
	if(node == 0) return 0;

	int leftHeight = calculate_tree_height(node->c0);
	int rightHeight = calculate_tree_height(node->c1);

	if(leftHeight > rightHeight) return leftHeight+1;
	else return rightHeight+1;
}

void HCTree::serialize_tree_level(HCNode* node, int level){
	if(node == 0) return;
	if(level == 1){
		vertex.push_back(node);	
		// cout << "Symbol: ";
		// if(node->symbol == 0xFF) cout << "node";
		// else cout << (char)node->symbol;
		// cout << ",  count=" << node->count;
		// cout << ",  child=" << node->child;
		// cout << endl;
	}
	else{
		serialize_tree_level(node->c0,level-1);
		serialize_tree_level(node->c1,level-1);
	}
}

void HCTree::write_padding_bit(unsigned long total, BitOutputStream& out){
	// Calculate the correct number of paddings by
	// calculating the total bits needed to write
	// then see how many more bits are needed to finish it.
	cout << "Total bit so far is " << total << endl;
	for(int i = 0; i < leaves.size(); i++){
		HCNode* node = leaves[i];
		if(node != 0){
			cout << "i: " << i << endl;
			unsigned int bits = node->count * get_depth(node);
			total += bits;
		}
	}
	cout << "Made it through for loop" << endl;
	total += 3l;
	int padding = total % 8;
	padding = 8 - padding;
	out.writeBit(padding & 4);
	out.writeBit(padding & 2);
	out.writeBit(padding & 1);
	cout << "padding is: " << padding << endl;
}

int HCTree::get_depth(HCNode* node){
	if(node == root) return 0;
	else return (get_depth(node->p) + 1);
}

unsigned long HCTree::write_tree_structure(BitOutputStream& out){
	unsigned long total = 0l;
	for(int i = 0; i < vertex.size(); i++){
		HCNode* node = vertex[i];
		if(node->symbol == 0xFF){
			out.writeBit(0);
			total++;
		} 
		else{
			out.writeBit(1);
			for(int k = 0; k < 8; k++){
				char temp = node->symbol;
				temp = temp << k;
				temp = temp >> (7-k);
				out.writeBit((int)temp);
			}
			total += 9;
		}
	}
	return total;
}



