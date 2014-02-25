#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    vector<HCNode*> vertex;
    priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp>* forest;
    unsigned long totalBitLength;

    // Private Helper Functions
    void delete_node(HCNode**);
    void print_node_path(HCNode *, BitOutputStream&) const;
    void serialize_tree();
    int calculate_tree_height(HCNode*);
    void serialize_tree_level(HCNode*, int);
    unsigned long write_tree_structure(BitOutputStream&);
    void write_padding_bit(unsigned long, BitOutputStream&);
    int get_depth(HCNode*);

public:
    explicit HCTree() : root(0) {
        totalBitLength = 0l;
        leaves = vector<HCNode*>(256, (HCNode*) 0);
        forest = new priority_queue<HCNode*,std::vector<HCNode*>, HCNodePtrComp >();
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

    /** Writes the header to given stream.
     *  First serialize the tree structure into array
     *  Then reads each node, print 0 if it is not a leaf
     *  If it is a leaf, print 1 followed by its 8bit char symbol.
     *  Then calculate all the bits needed to write and find out
     *  the padding needed, write the 3bit padding information to stream.
     */ 
    void generate_header_bits(BitOutputStream & out);

    void retrieve_tree_structure(BitInputStream & in);
};

#endif // HCTREE_HPP
