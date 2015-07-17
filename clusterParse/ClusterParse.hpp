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
*/


#ifndef CLUSTERPARSE_HPP_INCLUDED
#define CLUSTERPARSE_HPP_INCLUDED 1

#include <string>
#include <vector>



class ClusterParse{

public:

  ///<Constructor creates an empty clusterparser
  ClusterParse();

  ///<Destructor.
  ~ClusterParse();

  /*
   *    A struct used to describe a node in the tree
   */
  struct Record {

    bool leftChild_;              // A bool which is set to true when the left
                                  //     child is added. 
    bool rightChild_;             // A bool which is set to true when the right child
                                  //     is added.  
    size_t left_;                 // Index to the left child in the vector

    size_t right_;                // Index to the right child in the vector
    
    size_t parent_;               // Index of the parent in the vector
    
    int height_;                   // The height of the node from the bottom of the tree. 
                                  // contains the height of the maximum daughter node + 1. 

    //Our default constructor creates a struct with all values set to 0. 
    Record()
    {
      leftChild_ = false;
      rightChild_ = false; 
      left_ = 0; 
      right_ = 0; 
      parent_ = 0; 
      height_ = 0; 
    }
  };

  /* Sets the parent's node to the child. */ 
  void setChild(size_t child, size_t parent); 

  /* Sets the "parent" data member of the child node to the index passed. */ 

  void setParent(size_t child, size_t parent); 

  /* Returns true if the parent's left child is set; 
   *     and false if it is not. 
   */
  bool leftChild(size_t parent);

  /* Returns true if the parent's right child is set; 
   *     and false if it is not. 
   */
  bool rightChild(size_t parent); 

  /* Returns a size_t which specifies the location of the left child
   *     of the parent node within the array. 
   */ 
  size_t getLeftChild(size_t parent); 

  /* Returns a size_t which specifies the location of the right child
   *     of the parent node within the array. 
   */ 
  size_t getRightChild(size_t parent); 

  /* Returns the height from the bottom of the tree of the node passed  */ 
  size_t getHeight(size_t node); 

  /* Returns the parent of the specified child node if set, 0 otherwise. */ 

  size_t getParent(size_t child); 

  /* sets the right child of the parent node to the child size_t. */ 
  void setRightChild(size_t child, size_t parent); 

  /* sets the left child of the parent node to the child size_t. 
  */ 
  void setLeftChild(size_t child, size_t parent);

  /* Given a size_t which is the index of the child node, and a size_t
   *     which is the index of the parent node, this function adds
   *     the parent node to the array, and sets the child_ and parent_
   *     data members of both nodes appropriately.       
  */ 

  std::ostream& printTree(std::ostream& out); 


  std::ostream& printNode(size_t node, std::ostream& out); 


  void insert(size_t child, size_t parent);

  /*  Reads in from a file specified, and creates the vector data structure
   *      from that.  The vector contains the cluster-tree.  Each node can
   *      be accessed by indexing into its location in the vector.  
   * 
   */ 
  void readIn(std::ifstream& inputstream);

  /* Prints out the ClusterTree_ data struture, with each line 
   *     containing the index of the parent within the array. */ 

  void printChildren(size_t parent); 
 
private:

  /*  clusterTree_ contains a vector, which contains the hierarchical tree 
   *      created from the textfile.  Each element in the vector contains an
   *      int which is the index of its parent, as well as two ints which are
   *      its children in the tree.    
   */ 
  std::vector<Record> clusterTree_;

  size_t numRecords_; 


};

#endif // CLUSTERPARSE_HPP_INCLUDED
