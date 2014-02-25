#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <queue>
#include <bitset>
using namespace std;

void HCTree::delete_node(HCNode* node){
	if(node->c0 != 0) delete_node(node->c0);
	if(node->c1 != 0) delete_node(node->c1);
	delete node;
}

// Destructor
HCTree::~HCTree(){
	delete leaves;
	delete vertex;
	// Delete all nodes created in build().
	delete_node(root);
}


void HCTree::build(const vector<int>& freqs){
	// Initialize the priority queue.
    priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp>* forest = 
    					new priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp>();

	// Insert all non-zero frequencies into the priority queue
   	// Nodes created in for loop are all leaves, so mark with true.
	for(int i = 0; i < freqs.size(); i++){
		if(freqs[i] > 0){
			HCNode* node = new HCNode(freqs[i],(unsigned)i, true);
			(*leaves)[i] = node;
			forest->push(node);	
		}
	}
	// Using priority queue to build Huffman coding tree
	// New nodes created below are not leaves, so mark them with false
	while(forest->size() > 1){					// If size = 1, we have the tree we want
		HCNode* node_1 = forest->top();
		forest->pop();
		HCNode* node_2 = forest->top();
		forest->pop();
		HCNode* parent = new HCNode(
			node_1->count + node_2->count, 0, false, node_1, node_2);
		node_1->p = parent;
		node_2->p = parent;
		node_1->child = 0;
		node_2->child = 1;
		forest->push(parent);
	}
	if(forest->size() > 0){
		root = forest->top();
		forest->pop();
	}
	// Purpose of priority queue is accomplished, so destroy it here.
	delete forest;
}

void HCTree::generate_header_bits(BitOutputStream& out){
	//Serialize tree into array
	serialize_tree();
	//Write tree structure to file
	unsigned long bitsWritten = write_tree_structure(out);
	//Calculate total bits needed to write and the padding needed
	write_padding_bit(bitsWritten, out);
}


void HCTree::encode(byte symbol, BitOutputStream& out) const{
	HCNode* node = (*leaves)[(unsigned int)symbol];
	if(node != root)
		print_node_path(node, out);
}


void HCTree::rebuild(BitInputStream& in) {
	queue<HCNode*> * nodes = new queue<HCNode*>();
	HCNode* parent = 0;
	HCNode* newNode = 0;

	// Read first node
	int bit = in.readBit();
	if(bit == 0) nodes->push(newNode=new HCNode(0,0,false));	 
	else if (bit == 1){
		char result = retrieve_byte_value(in);
		newNode = new HCNode(0,result,true);
	}
	root = newNode;

	while(nodes->size() > 0){
		parent = nodes->front();
		nodes->pop();
		// Add to left child of parent
		bit = in.readBit();
		if(bit == 0) nodes->push(newNode=new HCNode(0,0,false));
		else if (bit == 1){
			char result = retrieve_byte_value(in);
			newNode = new HCNode(0,result,true);
		}
		parent->c0 = newNode;
		// Add to right child of parent
		bit = in.readBit();
		if(bit == 0) nodes->push(newNode=new HCNode(0,0,false));
		else{
			char result = retrieve_byte_value(in);
			newNode = new HCNode(0,result,true);
		}
		parent->c1 = newNode;
	}	
	delete nodes;

	// Debug:
	print_tree();

	// Read the padding bits and record its value in "unsigned int padding" variable
	unsigned int padding = 0;
	for(int i = 2; i >= 0; i--){
		unsigned int bit = in.readBit();
		bit = bit & 0x01; //just to make sure sign stuff..
		bit <<= i;
		padding |= bit;
	}
	// Read in the padding bits and discard them.
	for(unsigned int i = 0; i < padding; i++) in.readBit();
}




// loop through the rest of the bits
// Decode them and return value
int HCTree::decode(BitInputStream& in) const{
	HCNode* node = root;
	do{
		int bit = in.readBit();
		if(bit == 0) node = node->c0;
		else if(bit == 1) node = node->c1;
	} while(!(node->leaf));
	// Exit only when we reach a leaf
	return (unsigned int)node->symbol;
}


// Private Helper Function Implementations: For use by Public functions defined above.
// -----------------------------------------------------------------------------------

// Put tree nodes into an array (by breadth first)
void HCTree::serialize_tree(){
	int height = calculate_tree_height(root);
	for(int i = 1; i <= height; i++){
		serialize_tree_level(root, i);
	}
}

unsigned long HCTree::write_tree_structure(BitOutputStream& out){
	unsigned long total = 0l;
	for(unsigned int i = 0; i < vertex->size(); i++){
		HCNode* node = vertex->at(i);
		// If node is a leaf, write '1' followed by symbol
		if(node->leaf){
			out.writeBit(1);
			for(int k = 0; k < 8; k++){
				unsigned char temp = node->symbol;
				temp = temp >> (7-k);
				temp &= 0x01;
				out.writeBit((int)temp);
			}
			total += 9l;
		}
		else{
			out.writeBit(0);
			total += 1l;
		}
	}	
	return total;
}

void HCTree::write_padding_bit(unsigned long bitsWritten, BitOutputStream& out){
	// Total bits will be written to file is:
	// header bits + padding bits + encoded bits
	unsigned long headerBits = bitsWritten;
	unsigned long paddingBits = 3l;
	unsigned long encodedBits = 0l;

	// Traverse through the serialized tree:
	// count * path_lengh => total bits for that node symbol
	// cout << "Vertex size: " << vertex->size() << endl;
	for(unsigned int i = 0; i < vertex->size(); i++){
		HCNode* node = vertex->at(i);
		if(node->leaf){
			unsigned long bits = node->count * get_depth(node);
			encodedBits += bits;
		}
	}

	// Get total bits and % by 8
	unsigned long total = headerBits + paddingBits + encodedBits;
	if (total == 3l) return;		// input is an empty file
	unsigned int padding = (unsigned int)(total % 8);
	if(padding != 0) padding = 8 - padding;
	out.writeBit(padding & 4);
	out.writeBit(padding & 2);
	out.writeBit(padding & 1);

	// FIll the padding right away:
	for(unsigned int i = 0; i < padding; i++)
		out.writeBit(0);

	//Debuggin:
	// cout << "Header bits written: " << headerBits << endl;
	// cout << "Padding bits written: " << paddingBits << endl;
	// cout << "Encoded bits written: " << encodedBits << endl;
	// cout << "Total bits is: " << total << endl;
	// cout << "Total mod 8 is: " << total%8 << endl;
	// cout << "Based on this info, the padding value is: " << padding << endl;
}

unsigned long HCTree::get_depth(HCNode* node){
	if(node == root) return 0;
	else return (get_depth(node->p)+1);
}


void HCTree::print_node_path(HCNode* node, BitOutputStream& out) const{
	if(node->p != root)
		print_node_path(node->p,out);
	out.writeBit(node->child);
}

// Calculate and return the depth at current node
int HCTree::calculate_tree_height(HCNode* node){
	if(node == 0) return 0;

	int leftHeight = calculate_tree_height(node->c0);
	int rightHeight = calculate_tree_height(node->c1);

	if(leftHeight > rightHeight) return leftHeight+1;
	else return rightHeight+1;
}

// Put nodes at this level into array
void HCTree::serialize_tree_level(HCNode* node, int level){
	if(node == 0) return;
	if(level == 1){
		vertex->push_back(node);	
	}
	else{
		serialize_tree_level(node->c0,level-1);
		serialize_tree_level(node->c1,level-1);
	}
}

unsigned char HCTree::retrieve_byte_value(BitInputStream& in){
	bitset<8> buf;
	buf.reset();
	for(int i = 7; i >= 0; i--){
		buf[i] = in.readBit();
	}
	return (unsigned char)buf.to_ulong();
	// unsigned char result = 0;
	// for(int i = 7; i >= 0; i--){
	// 	unsigned char bit = (unsigned char)in.readBit();
	// 	bit <<= i;
	// 	result |= bit;
	// }
	// return result;
}


void HCTree::print_tree(){
	cout << "Printing tree structure: " << endl;
	int height = calculate_tree_height(root);
	cout << "  height = " << height << endl;

	queue<HCNode*>* nodes = new queue<HCNode*>();
	nodes->push(root);
	while(nodes->size() > 0){
		HCNode* node = nodes->front();
		nodes->pop();
		cout << "  " << *node;
		if(node->leaf) cout << "  leaf";
		cout << endl;
		if(node->c0 != 0) nodes->push(node->c0);
		if(node->c1 != 0) nodes->push(node->c1);
	}
}














