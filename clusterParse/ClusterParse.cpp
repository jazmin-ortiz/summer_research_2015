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
    vector<Node> clusterArray;
    clusterTree_ = clusterArray;
    numRecords_ = 0;
}

// Destructor for the ClusterParse
ClusterParse::~ClusterParse(){
    // Do nothing here
}


/* Given a child node and a parent node, sets the parent's
 *    child node if one is available, and throws an error if
 *    one is not.  */
void ClusterParse::setChild(size_t child, size_t parent){
    //If there is no left child...
    if (leftChild(parent) == false){
        //Set it.
        setLeftChild(child, parent);
    }
    else {
        //If there is a left child, but no right child
        if(rightChild(parent) == false){
            //set the right child instead.
            setRightChild(child, parent);
        }
        else {
            //Otherwise, throw an error.
            std::cout << "Error:  Input tree is not a binary Tree; " <<
            "too many child nodes" << std::endl;
        }
    }
}

/* Returns the contents of the left_ data member of the parent node.
 *     In an ideal world, this would always contain the index of the left
 *     child.  On the other hand, it is possible to call this function on
 *     a node which has not had the left child initialized.  This will Cause
 *     Problems; do not do that. */
size_t ClusterParse::getLeftChild(size_t parent){
    return clusterTree_[parent].left_;
}

/* Returns the contents of the right_ data member of the parent node.
 *     In an ideal world, this would always contain the index of the right
 *     child.  On the other hand, it is possible to call this function on
 *     a node which has not had the right child initialized.  This will Cause
 *     Problems; do not do that. */
size_t ClusterParse::getRightChild(size_t parent){
    return clusterTree_[parent].right_;
}


/* Sets the left child of a parent node.  One thing to note about
 *     this function is that it does not (1) check for the feasibility
 *     of setting the left child in terms of existance within the vector
 *     of parent or child, the previous existance of a left child, or
 *     anything else.  That happens in "insert" and "setChild" */
void ClusterParse::setLeftChild(size_t child, size_t parent){
    clusterTree_[parent].leftChild_ = true;
    clusterTree_[parent].left_ = child;
    // Because we always try to set the left child first, we don't
    //     need to check if the height from the right child is greater.
    clusterTree_[parent].height_ = clusterTree_[child].height_ + 1;
}


/* Sets the right child of a parent node.  One thing to note about
 *     this function is that it does not (1) check for the feasibility
 *     of setting the left child in terms of existance within the vector
 *     of parent or child, the previous existance of a right child, or
 *     anything else.  That happens in "insert" and "setChild" */
void ClusterParse::setRightChild(size_t child, size_t parent){
    clusterTree_[parent].right_ = child;
    clusterTree_[parent].rightChild_ = true;
    //If the height of the right child is greater than the previous height...
    if (clusterTree_[parent].height_ - 1 < clusterTree_[child].height_){
        // Update the height datamember to reflect the latest height.
        clusterTree_[parent].height_ = clusterTree_[child].height_ + 1;
  }
}

/*  Returns true if there is already left child
 *      for the parent and false if there is not.  */
bool ClusterParse::leftChild(size_t parent){
    //Return true if there is a left child, or false otherwise.
    return clusterTree_[parent].leftChild_;
}

/*  Returns true if there is already right child
 *      for the parent and false if there is not.  */
bool ClusterParse::rightChild(size_t parent){
    //Return true if there is a right child, or false otherwise.
    return clusterTree_[parent].rightChild_;
}

/* Checks to see if the node "parent" has child node "child" */ 
bool ClusterParse::isChild(size_t child, size_t parent){
    if (leftChild(parent) == true && getLeftChild(parent) == child)
        return true;
    if (rightChild(parent) == true && getRightChild(parent) == child){
        return true;
    }
    return false; 
}

/* Returns the idex of the parent of a child node passed. Again,
 *     assumes the child should exist, and the parent data member
 *     must be initialized to a nonzero number. */
size_t ClusterParse::getParent(size_t child){
    size_t parent = clusterTree_[child].parent_;
    if (parent == 0){
    }
    return parent;
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

/* Returns the height of the any given node.  If the depth of the left and right
 *     subtrees differs, then this function reports the greater of the possible
 *     heights.   It is worth noting that because of this, the height does not
 *     always increment/decrement by one per node as the tree is traversed upwards
 *     and down. */
size_t ClusterParse::getHeight(size_t node) {
    return clusterTree_[node].height_;
}

/*  Inserts a node, based on the line read in from a cluto output record.
 *     NOTE:  Should check for a valid parent value before it is added. */
void ClusterParse::insert(size_t child, size_t parent){
    numRecords_ += 1;
    std::cout.flush(); 

    //First, we check and see if the vector is large enough.
    size_t vectorSize = clusterTree_.size();
    if (vectorSize <= parent){
        /* If the parent would take us off the end of the array,
         *     we increase the size until the vector can contain
         *     the parent. */
        for (size_t i = 0; i <= (parent - vectorSize); ++i){
            Node newNode;
            newNode.height_ = 0;
            newNode.leftChild_ = false;
            newNode.rightChild_ = false;
            newNode.parent_ = 0;
            clusterTree_.push_back(newNode);
        }
    }
    /* Otherwise, we set the child's parent. */
    setParent(child, parent);
    /* ...and the parent's child.*/
    setChild(child, parent);
}

/* A wrapper function for printNode.  This function prints out the nodes of the tree
 *     in a reasonable order (the order that they are stored in the internal data
 *     structure. */
std::ostream& ClusterParse::printTree(std::ostream& out){
    /* Most of the work for this function is done in printNode, recursively.
    * This is just a wrapper function. */
    printNode(numRecords_, out);
    return out;  

}

/* A helper function for any print functions.  While it is currently only called
 *     by printTree, which prints the entire tree, it prints the subtree of
 *     any nodes passed to it.  It is worth noting that for our purposes, we
 *     do not need to print out the internal structure of the tree, only the
 *     leaves. */
std::ostream&ClusterParse::printNode(size_t node, std::ostream& out){
    bool left = leftChild(node);
    bool right = rightChild(node);
    if (left == false && right == false){
    /* We begin by checking if we are at a leaf.
    * If we are, we print the associated number. */
        out << node;
    }
    else{
        if (left == true && right == false){
            /*If we have a left tree, but no right, print the left subtree */
            out << "(";
            printNode(getLeftChild(node), out);
            out <<  ", " << node << ")";
        }
        if (left == true && right == true){
            /*If we have both, print both subtrees */
            out << "(";
            printNode(getLeftChild(node), out);
            out << ", " << node << ", ";
            printNode(getRightChild(node), out);
            out << ")";
        }
        if (left == false && right == true){
            out << "( , " << node << ", ";
            /* If we just have the right, print that one. */
            printNode(getRightChild(node), out);
            out << ")";
        }
    }
    return out; 
}

/* A function created for use in debugging; prints out the
 *     data members of a node index passed to it. */
void ClusterParse::printChildren(size_t parent){
    std::cout << "###PARENT IS " << parent << "###" << std::endl;
    std::cout << "leftChild_ is " << clusterTree_[parent].leftChild_ <<
                 "\n Left Child is " << clusterTree_[parent].left_ <<
                 "\n rightChild_ is " << clusterTree_[parent].rightChild_ <<
                 "\n Right Child is " << clusterTree_[parent].right_ <<
                 "\n Parent is " << clusterTree_[parent].parent_ << std::endl;
}

/* */
void ClusterParse::readIn(ifstream& inputstream)
{
    /* The most recently read character and an accumulator to hold the
     *     numbers that are read in as a string from stdin until we are
     *     ready to process them.  */
    char c;
    string parentIndex = "";
    size_t counter = 0; /* Keeps track of how many lines we have already seen, or the
                         * identity of the current line. */

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
            if ( c == '\n' ) {
                //We check to make sure that we are not at the root...
                if (parentIndex != "-1"){
                    size_t value = stoi(parentIndex); 
                    insert(counter, value);
                    parentIndex = "";
                    counter += 1;
                } 
                else {
                    //We keep track of the root by making its "parent" itself.
                    clusterTree_[counter].parent_ = counter;
                }
            //If we are at the root, then we are done.
            parentIndex = "";
            }
            else {
                /* Otherwise we append the character we just read to our accumulator and
                 *     continue reading. */
                parentIndex.push_back(c);
            }
    }
    inputstream.close();
}



