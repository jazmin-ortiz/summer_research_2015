/*
 * Clusterparse.cpp
*/

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <unordered_map>

#include "ClusterParse.hpp"

using namespace std;

// Default constructor for ClusterParse
ClusterParse::ClusterParse(){
    vector<Record> clusterArray; 
    clusterTree_ = clusterArray;  
}

// Destructor for the ClusterParse
ClusterParse::~ClusterParse()
{
  // Do nothing here
}


/* Given a child node and a parent node, sets the parent's
 *    child node, if one is available, and throws an error if
 *    one is not.  */ 

void ClusterParse::setChild(size_t child, size_t parent){
  std::cout << "Child in setChild is " << child << std::endl; 
  std::cout << "Parent is " << parent << std::endl; 
  //If there is no left child... 
  std::cout << leftChild(parent) << std::endl; 
  if (leftChild(parent) == false){
    //Set it.  
      setLeftChild(child, parent);
  } 
  else {
    //If there is a left child, but no right child
      if(rightChild(parent) == false){
        //set the right child instead. 
        setRightChild(child, parent);
        std::cout << "setting the right child" << std::endl; 
      } 
      else {
        //Otherwise, throw an error. 
        std::cout << "Error:  Input tree is not a binary Tree; " <<
        "too many child nodes" << std::endl; 
      }
  }
}

/* Given a child and a parent node, sets the child node's parent_
 *    data member to the parent size_t passed.  If the parent node
 *    is already set to another node, it throws an error.  
 *
*/ 
void ClusterParse::setParent(size_t child, size_t parent){
  //If the child has already been set to a different parent previously, then we have 
  // a problem in our parsing of the tree. 
    if (getParent(child) != (size_t) 0 && getParent(child) != parent){
      std::cout << "The parent has already been set to another value" << std::endl; 
      std::cout << "The previous parent was: " << getParent(child) << std::endl; 
      std::cout << "The new parent is: " << getParent(child) << std::endl; 
    }  
    else{
      //Otherwise, we can just set the parent. 
      clusterTree_[child].parent_ = parent; 

    }

}


/*  Returns true if there is already left child  
 *      for the parent and false if there is not. 
 */ 
bool ClusterParse::leftChild(size_t parent){
  //Return true if there is a left child, or false otherwise.
    return clusterTree_[parent].leftChild_; 
}

/*  Returns true if there is already right child  
 *      for the parent and false if there is not. 
 */ 
bool ClusterParse::rightChild(size_t parent){
  //Return true if there is a right child, or false otherwise. 
    return clusterTree_[parent].rightChild_; 
}


void ClusterParse::setLeftChild(size_t child, size_t parent){
  std::cout << "child is " << child << std::endl; 
  std::cout << "parent is " << parent << std::endl; 
  clusterTree_[parent].leftChild_ = true;  
  clusterTree_[parent].left_ = child; 
  printChildren(parent);

  // Because we always try to set the left child first, we don't
  //     need to check if the height from the right child is greater. 

  clusterTree_[parent].height_ = clusterTree_[child].height_ + 1; 

}


void ClusterParse::setRightChild(size_t child, size_t parent){
  clusterTree_[parent].right_ = child; 
  clusterTree_[parent].rightChild_ = true; 

  //If the height of the right child is greater than the previous height...
  if (clusterTree_[parent].height_ - 1 < clusterTree_[child].height_){
    // Update the height datamember to reflect the latest height. 
    clusterTree_[parent].height_ = clusterTree_[child].height_ + 1; 
  }
}

size_t ClusterParse::getParent(size_t child){
    return clusterTree_[child].parent_;    

}

size_t ClusterParse::getRightChild(size_t parent){
  return clusterTree_[parent].right_; 

}

size_t ClusterParse::getLeftChild(size_t parent){
  return clusterTree_[parent].left_; 

}

void ClusterParse::printChildren(size_t parent){
  std::cout << "###PARENT IS " << parent << "###" << std::endl; 
  std::cout << "leftChild_ is " << clusterTree_[parent].leftChild_ <<
               "\n Left Child is " << clusterTree_[parent].left_ << 
               "\n rightChild_ is " << clusterTree_[parent].rightChild_ <<
               "\n Right Child is " << clusterTree_[parent].right_ << 
               "\n Parent is " << clusterTree_[parent].parent_ << std::endl; 
}

/*  Inserts a node, based on the line read in from a cluto output record. 
 *     NOTE:  Should check for a valid parent value before it is added. 
 */ 
void ClusterParse::insert(size_t child, size_t parent){
  std::cout << "Child in insert is " << child << 
               "\n Parent in insert is " << parent << std::endl; 
  //First, we check and see if the vector is large enough. 
  size_t vectorSize = clusterTree_.size(); 

  if (vectorSize <= parent){
      //if the parent would take us off the end of the array, 
      //  we increase the size until the vector can contain
      //  the parent. 
        for (size_t i = 0; i <= (parent - vectorSize); ++i){
          Record newRecord;  
          newRecord.height_ = 0; 
          newRecord.leftChild_ = false;
          newRecord.rightChild_ = false; 
          newRecord.parent_ = 0; 
          clusterTree_.push_back(newRecord); 
        }
  }

  //Otherwise, we set the child's parent. 
  setParent(child, parent); 

  //...and the parent's child.  
  setChild(child, parent);

}

/**
 * function: readIn(ifstream& inputstream)
 *
 * Reads in from standard in and changes the Sequence_, mapLBA_ and
 * mapPBA_ private data members apropriately using the insert function.
 */
void ClusterParse::readIn(ifstream& inputstream)
{

  /* 
   * The most recently read character and an accumulator to hold the 
   *     numbers that are read in as a string from stdin until we are
   *     ready to process them.  */ 
  char c;
  string parentIndex = "";

  size_t counter = 0; // Keeps track of how many lines we have already seen, or the
             // identity of the current line. 

  /* While loop to read in a text file from stdin. */ 
  while (inputstream.get(c)) {
    // If there is nothing more in the file, then we are done.  
    if (inputstream.eof()){
      return;
    }
    /* If we have hit a newline, it means that the end of the current index has
     *     been encountered, which means that we should insert it into our 
     *     clusterTree_ vector, after checking to make sure that it is not 
     *     the root. */ 
    else if ( c == '\n' ) {
      //We check to make sure that we are not at the root... 
      if (parentIndex != "-1"){
          insert(counter, stoi(parentIndex));
          parentIndex = "";
       } 
      //If we are at the root, then we are done. 
      parentIndex = ""; 
    }
    /* Otherwise we append the character we just read to our accumulator and 
     *     continue reading. */ 
    else {
      parentIndex.push_back(c);

    }
  }
  inputstream.close();
}




