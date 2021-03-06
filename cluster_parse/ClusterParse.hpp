/**
* \file ClusterParse.hpp
*
* Author: Elizabeth Krenkel
*         Modified from the TraceSet code by Jazmin Ortiz
* Last Modified: July 15, 2015
*
* This is a class callled ClusterParse, created to process the output of the
*    cluto clustering software (see http://glaros.dtc.umn.edu/gkhome/views/cluto)
*    for the code.
*
*    Presented with a text file (the output from that software, with the -fulltree
*    option specified), it reads in the file and uses that to reconstruct
*    the full hierarchical tree.
*
*    The internal representation of the tree is a one-dimensional array of structs.
*    each struct contains the index of both children, and the index of the parent.
*    The data is representeted as size_ts, because we don't know how big this is going
*    to get, and we are using a vector, so we can't use pointers to represent the
*    index.  The booleans leftChild_ and rightChild_ are used to check if the children
*    are set.  For a parent, it is possible to just initialize every parent to 0.  In that
*    way we can check if the parent is set, because 0 is necessarily a leaf, and no one's
*    parent.  The same cannot be said of children nodes.
*   
* Meant to eventually be included in the TraceSet data structure. 
*
*/


#ifndef CLUSTERPARSE_HPP_INCLUDED
#define CLUSTERPARSE_HPP_INCLUDED 1

#include <string>
#include <vector>

class ClusterParse{

public:

    /* <Constructor creates an empty clusterParse. */
    ClusterParse();

    /* <Destructor. */
    ~ClusterParse();

    /*  A struct used to describe a node in the tree structure */
    struct Node {

    bool leftChild_;              /* A bool which is set to true when the left
                                   *     child is added. */
    bool rightChild_;             /* A bool which is set to true when the
                                   *      right child is added. */
    std::size_t left_;                 /* Index to the left child in the vector */

    std::size_t right_;                /* Index to the right child in the vector */

    std::size_t parent_;               /* Index of the parent in the vector */

    int height_;                  /* The height of the node from the bottom
                                   *      of the tree. contains the
                                   *      height of the maximum daughter
                                   *      node + 1. */
};
///Data structure management functions///

    /* Returns true if the child node is a child of the parent node. */ 
    bool isChild(std::size_t child, std::size_t parent); 

    /* Returns a size_t which specifies the location of the left child
     *     of the parent node within the array. */
    std::size_t getLeftChild(std::size_t parent);

    /* Returns a size_t which specifies the location of the right child
     *     of the parent node within the array. */
    std::size_t getRightChild(std::size_t parent);

    /* Returns true if the parent's left child is set;
     *     and false if it is not. */
    bool leftChild(std::size_t parent);

   /* Returns true if the parent's right child is set;
    *     and false if it is not.  */
    bool rightChild(std::size_t parent);

    /* Returns the parent of the specified child node if set, 0 otherwise. */
    std::size_t getParent(std::size_t child);

    /* Returns the height from the bottom of the tree of the node passed  */
    std::size_t getHeight(std::size_t node);

    /* Returns the root of the tree. */ 
    std::size_t getRoot(); 

///Printing and I/O functions///

    /* Uses the helper functions above to appropriately insert
     * a new node and set the parent-child relationships appropriately. */
    void insert(std::size_t child, std::size_t parent);

    /* Prints the entire tree. */ 
    std::ostream& printTree(std::ostream& out);

    /* A helper function for the printTree function.  Recursively prints the 
     * subtree below the node passed as initial argument. */ 
    std::ostream& printNode(std::size_t node, std::ostream& out);
    
    /* A debugging function which prints all of the data members of the
     *     node specified by the argument. */
    void printChildren(std::size_t parent);

    /*  Reads in from a file specified. */
    void readIn(std::ifstream& inputstream, bool test);

    std::vector<std::size_t> readRemap(std::ifstream& inputstream); 

    /* Creates a vector a size_ts in the order of leaves on the tree.  
     *     Created to pass the vector to the TraceSet data structure. */ 
    std::vector<std::size_t> formatOutput(std::vector<std::size_t> mapping); 

    /* A helper function for formatOutput which traverses the tree adding a node
     *     to the vector only when it is a leaf (with no children) and is therefore
     *     in the original adjacency matrix fed into the cluto algorithm. */ 
    void traverseTree(std::size_t node, std::vector<std::size_t>* leafList);

    /* A function which takes in a tree and returns an fstream object which
     *     contains the tree in the form of a Treefile, where the specifications
     *     of the Treefile format are given by Cluto: A clustering toolkit.*/
    std::fstream makeTreeFile();

   /*
    * A function that returns a vector of size_ts that represent the leaf nodes
    *      of the tree and thier order in the tree which is defined by thier
    *      parent. */
  std::vector<std::size_t>& getLeaves(std::vector<std::size_t>& leaves, std::size_t here);

private:


    /* Sets the parent's node to the child. */
    void setChild(std::size_t child, std::size_t parent);

    /* sets the left child of the parent node to the child size_t.  */
    void setLeftChild(std::size_t child, std::size_t parent);

    /* sets the right child of the parent node to the child size_t. */
    void setRightChild(std::size_t child, std::size_t parent);

    /* Sets the "parent" data member of the child node to the index passed. */
    void setParent(std::size_t child, std::size_t parent);

 

    std::vector<Node> clusterTree_; /* Contains the data structure of the
                                       * tree within an array. */
    std::size_t numNodes_;               /* Holds the number of records in the
                                       * tree, or the index of the root. 
                                       * NOTE:  DOES NOT CONTAIN THE NUMBER 
                                       *     OF ITEMS CLUSTERED. */ 
};

#endif // CLUSTERPARSE_HPP_INCLUDED

