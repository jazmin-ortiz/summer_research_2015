/**
 * \file trace-set-test.cpp
 *
 * \Authors Elizabeth Krenkel
 *
 *Partially tests a ClusterParse data structure for correctness.  Does
 *    not fully test, because we haven't really found a neat way of 
 *    constructing a large tree to test on, whose properties we know.  As
 *    such, we have a lot of small test cases (balanced tree, stick, etc). 
 *    and have visually checked the output of printTree() against the tree
 *    PDFs generated by the CLUTO package.      
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


/* Makes a tree from the file test1. */ 
ClusterParse fileTestTree(){
    ClusterParse test;
    string filename = "test1";
    ifstream testFile(filename);
    test.readIn(testFile, true); 
    return test; 
}
/* Makes and returns a stick with 3 elements. */ 
ClusterParse smallStickTree(){
    ClusterParse test; 
    test.insert(0, 1);
    test.insert(1, 2); 
    return test; 
}

/* Makes and returns a stick with 500 elements. */ 
ClusterParse largeStickTree(){
    ClusterParse test; 
        for (size_t i = 0; i < 500; ++i){
        test.insert(i, i + 1); 
    }
    return test; 
}

/* Makes and returns a balanced tree with 8 leaf nodes. */ 
ClusterParse balancedTree(){
    ClusterParse test; 
    size_t parent = 8; 
    for(size_t i = 0; i < 7; ++i){
        test.insert(i * 2, parent);
        test.insert(i * 2 + 1, parent);
        parent += 1; 
    }
    return test; 
}
/* Checks that we don't segfault.  We never intend
 *     to use this before it is read in, so we don't 
 *     bother to seriously test this. */ 
TEST(constructor, default_constructor)
{
    ClusterParse test; 
}

/* Tests getParent and isChild for a small stick. */ 
TEST(parentalRelations, smallStick){
    ClusterParse test = smallStickTree(); 
    assert(test.getParent(0) == 1);
    assert(test.getParent(1) == 2); 
    assert(test.isChild(0, 1)); 
    assert(test.isChild(1, 2)); 
}

/* Tests the getHeight function for a small stick. */ 
TEST(getHeight, smallStick){
    ClusterParse test = smallStickTree(); 
    assert(test.getHeight(0) == 0);
    assert(test.getHeight(1) == 1); 
    assert(test.getHeight(2) == 2);
}

/* Tests the getHeight function for a tree 
 *     read in from a testfile. Implicitly 
 *     also tests readIn. */ 
TEST(getHeight, fullTree){
    ClusterParse test = fileTestTree(); 

    assert(test.getHeight(0) == 0); 
    assert(test.getHeight(1) == 0);
    assert(test.getHeight(11) == 1);
    assert(test.getHeight(10) == 1); 
    assert(test.getHeight(14) == 2);
    assert(test.getHeight(16) == 3); 
    assert(test.getHeight(2) == 0);
    assert(test.getHeight(6) == 0);
    assert(test.getHeight(15) == 2); 
    assert(test.getHeight(17) == 4); 
    assert(test.getHeight(18) == 5); 
}

/* Tests getParent for a large stick. */ 
TEST(getParent, largeStick){
    ClusterParse test = largeStickTree(); 
    for (size_t i = 0; i < 500 - 1; ++i){
        assert(test.getParent(i) == i + 1); 
    }
}

/* Tests isChild for a large stick. */ 
TEST(isChild, largeStick){
    ClusterParse test = largeStickTree(); 
    for (size_t i = 1; i < 500; ++i){
        assert(test.isChild(i - 1, i) == true); 
    }
}

/* Tests getParent for a balanced tree. */ 
TEST(getParent, balencedTree){
    ClusterParse test = balancedTree(); 
    assert(test.getParent(0) == 8);
    assert(test.getParent(1) == 8); 
    assert(test.getParent(6) == 11); 
    assert(test.getParent(7) == 11);
    assert(test.getParent(11) == 13);
    assert(test.getParent(13) == 14); 
}

/*Tests getRoot for a balanced tree. 
 *    implicitly tests insert and the associated helper
 *    functions. */ 
TEST(getRoot, balencedTree){
    ClusterParse test = balancedTree(); 
    assert(test.getRoot() == 14); 
}

/* Tests getRoot on a large stick. Also implicitly tests
 *     insert and the associated helper functions. */ 
TEST(getRoot, largeStick){
    ClusterParse test; 
    for (size_t i = 0; i < 500; ++i){
        test.insert(i, i + 1); 
    }
    assert(test.getRoot() == 500); 

}

/* tests getRoot on a tree read in from a testfile. 
 *     implicitly tests readIn and insert, as well as
 *     setParent and setChild */ 
TEST(getRoot, fullTree){
    ClusterParse test = fileTestTree(); 
    assert(test.getRoot() == 18); 
}

/* Checks the properties of the vector from formatOutput for small
 *     trees. */ 
TEST(formatOutput, smallStick){
    ClusterParse test = smallStickTree(); 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector);

    assert(result.size() == 1); 
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == i); 
    }
}

TEST(formatOutput, fulllTree){
    ClusterParse test = fileTestTree(); 
    std::vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector); 
    test.printTree(cout); 

    std::cout << "formatOutput result is: " << std::endl; 
    for (size_t i = 0; i < result.size(); ++ i){
        cout << result[i] << ", ";
    }

    cout << endl; 

    assert(result[0] == 6);
    assert(result[1] == 1);
    assert(result[2] == 5);
    assert(result[3] == 3);
    assert(result[4] == 7);
    assert(result[5] == 2);
    assert(result[6] == 0);
    assert(result[7] == 4);
    assert(result[8] == 8);
    assert(result[9] == 9); 
}


TEST(formatOutput, largeStick){
    ClusterParse test = largeStickTree(); 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector); 

    assert(result.size() == 1); 
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == i); 
    }
}
/* Checks the properties of the vector from formatOutput for 
 *     a larger, balanced tree. */ 
TEST(formatOutput, balancedTree){
    ClusterParse test = balancedTree(); 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector);

    assert(result.size() == 8); 
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == i); 
    }
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
    ClusterParse test = fileTestTree(); 
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
    ClusterParse test = fileTestTree(); 

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

// test to make sure that formatOutput and formatOutputVector return the same
// vector
TEST(formatfunctions, small)
{
    ClusterParse test;
    test.insert(0, 3);
    test.insert(1, 3);
    test.insert(3, 5);
    test.insert(2, 4);
    test.insert(4, 5);

    vector<size_t> mappingVector; 

    vector<size_t> vector1 = test.formatOutput(mappingVector);
    vector<size_t> vector2 = test.formatOutputVector();

    cout << "Bat Elizabeth" <<endl;
    cout << vector1.size() <<endl;

    cout << "Jazmin" <<endl;
    cout << vector2.size() <<endl;

    assert(vector1.size() == vector2.size());

    for(size_t i = 0; i < vector1.size(); ++i) {
        assert(vector1[i] == vector2[i]);
    }
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
