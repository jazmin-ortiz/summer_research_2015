/**
 * \file trace-set-test.cpp
 *
 * \Authors Jazmin Ortiz
 *
 * \brief Tests a TraceSet for correctness
 */

#include "ClusterParse.hpp"
#include "gtest/gtest.h"

#include <memory>
#include <fstream>

using namespace std;

//--------------------------------------------------
//           TEST FUNCTIONS
//--------------------------------------------------

/// Test pushing back on an empty list (also tests default construction).

TEST(constructor, default_constructor)
{
    ClusterParse test; 
}


/// Test insert when taking in only the same character
TEST(getParent, smallTree)
{
    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    //Test that getParent works on a small tree... 
    assert(test.getParent(0) == 2);
    assert(test.getParent(1) == 2);
    assert(test.getParent(2) == 5); 
    assert(test.getParent(3) == 4); 
    assert(test.getParent(4) == 5); 
}

/// Test insert when taking in only the same character
TEST(getChild, smallTree)
{
    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    //Test that getParent works on a small tree... 
    assert(test.getLeftChild(2) == 0);
    assert(test.getRightChild(2) == 1);
    assert(test.getLeftChild(4) == 3); 
    assert(test.getLeftChild(5) == 2); 
    assert(test.getRightChild(5) == 4); 
}


/// Test insert when taking in only the same character
TEST(child_existance, smallTree)
{
    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    //Test that getParent works on a small tree... 

    //First, we check on the leaves... 
    assert(test.leftChild(0) == false); 
    assert(test.rightChild(0) == false); 
    assert(test.rightChild(1) == false); 
    assert(test.leftChild(1) == false); 
    assert(test.leftChild(3) == false); 
    assert(test.rightChild(3) == false);

    //Then the ones with one child... (it should be the left)

    assert(test.leftChild(4) == true); 
    assert(test.rightChild(3) == false); 

    //Then the ones with two... 
    assert(test.rightChild(2) == true); 
    assert(test.leftChild(2) == true); 
    assert(test.rightChild(5) == true);
    assert(test.leftChild(5) == true); 

}

TEST(parent, fullTree){
    ClusterParse test;
    string filename = "test1";
    ifstream testFile(filename);
    test.readIn(testFile); 
    assert(test.getParent(15) == 18); 
    assert(test.getParent(17) == 18);
    assert(test.getParent(13) == 15); 
    assert(test.getParent(1) == 13);
    assert(test.getParent(5) == 13); 
    assert(test.getParent(8) == 11);
    assert(test.getParent(9) == 11); 
    assert(test.getParent(0) == 10);
    assert(test.getParent(7) == 12);
}

TEST(children, fullTree){
    ClusterParse test;
    string filename = "test1";
    ifstream testFile(filename);
    test.readIn(testFile); 

    assert(test.isChild(15, 18));
    assert(test.isChild(7, 12)); 
    assert(test.isChild(3, 12)); 
    assert(test.isChild(0, 10));
    assert(test.isChild(17, 18));
    assert(test.isChild(12, 17)); 
    assert(test.isChild(3, 12)); 
    assert(test.isChild(2, 16));
    assert(test.isChild(8, 11));
    assert(test.isChild(4, 10)); 
    assert(test.isChild(1, 13)); 
    assert(test.isChild(5, 13));

}



//--------------------------------------------------
//           RUNNING THE TESTS
//--------------------------------------------------

/// Run test
int main(int argc, char** argv)
{
    // Initalize testing environment
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
