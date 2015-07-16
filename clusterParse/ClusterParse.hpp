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
*    The internal representation of the tree is a one-dimension   
*
*
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

  void insert(size_t child, size_t parent);

  /*  Reads in from a file specified, and creates the vector data structure
   *      from that.  The vector contains the cluster-tree.  Each node can
   *      be accessed by indexing into its location in the vector.  
   * 
   */ 
  void readIn(std::ifstream& inputstream);
 
private:

  /*  clusterTree_ contains a vector, which contains the hierarchical tree 
   *      created from the textfile.  Each element in the vector contains an
   *      int which is the index of its parent, as well as two ints which are
   *      its children in the tree.    
   */ 
  std::vector<Record> clusterTree_;


};

#endif // CLUSTERPARSE_HPP_INCLUDED
