/**
 * \file cluster-parse-test.cpp
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
ClusterParse fullTree1(){
    ClusterParse test;
    string filename = "test1";
    ifstream testFile(filename);
    test.readIn(testFile, true); 
    return test; 
}

/* Makes a tree to test on from the file test2 */ 
ClusterParse fullTree2(){
    ClusterParse test; 
    string filename = "test2"; 
    ifstream testFile(filename);
    test.readIn(testFile, true);
    return test; 
}

/* Returns a vector of the leaves of the tree from 
 *     test1 file, in the order that they should appear 
 *     in the tree from left to right. */ 
vector<size_t> result_fullTree1(){
    /* We create a vector...*/ 
    vector<size_t> resultVector; 
    /* Fill it with what the contents of
     *     formatOutput should be for test1...*/
    resultVector.push_back(6);
    resultVector.push_back(1);
    resultVector.push_back(5);
    resultVector.push_back(3);
    resultVector.push_back(7);
    resultVector.push_back(2);
    resultVector.push_back(0);
    resultVector.push_back(4);
    resultVector.push_back(8);
    resultVector.push_back(9);

    /* And return it for use in other functions. */ 
    return resultVector; 
}

/* Returns a vector of the leaves of the tree from 
 *     test2 file, in the order that they should appear 
 *     in the tree from left to right. */ 
vector<size_t> result_fullTree2(){
    /* We create a vector...*/ 
    vector<size_t> result; 
    /* Fill it with what the contents of
     *     formatOutput should be for test2...*/
    result.push_back(0);
    result.push_back(1);
    result.push_back(5); 
    result.push_back(4);
    result.push_back(6);
    result.push_back(2);
    result.push_back(10);
    result.push_back(3);
    result.push_back(9);
    result.push_back(7);
    result.push_back(8);
    /* And return it for use in other functions. */ 
    return result; 
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
TEST(getHeight, fullTree1){
    ClusterParse test = fullTree1(); 
    /*  These results are determined by prior knowledges
     *      of the graph. */ 
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
TEST(getRoot, balancedTree){
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
    ClusterParse test = fullTree1(); 
    assert(test.getRoot() == 18); 
}

/* Checks that FormatOutput works for a small stick with a single leaf. */ 
TEST(formatOutput, smallStick){
    ClusterParse test = smallStickTree(); 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector);
    
    /* We check that the output of FormatOutput for a stick with a 
     *     single leaf is the single number that we expect. */  
    assert(result.size() == 1); 
    assert(result[0] == 0); 
}

/* Checks that formatOutput works for a a tree made from the file test1. 
 *     with no remapping. */
TEST(formatOutput, fullTree){
    ClusterParse test = fullTree1();
    /* We are not interested in checking remapping at this point, so we 
     *     pass an empty vector as the argument to formatOutput. */  
    vector<size_t> testVector; 
    vector<size_t> result = test.formatOutput(testVector); 

    /* We get a vector to check against. */ 
    vector<size_t> checkVector = result_fullTree1();

    /* We perform a preliminary check to make sure our vectors are the
     *     same size... */ 
    assert(checkVector.size() == result.size()); 

    /* Then we check that every element in our result and the expected
     *     result are the same. */ 
    for (size_t i = 0; i < checkVector.size(); ++i){
        assert(result[i] == checkVector[i]); 
    }
}


/* Checks that formatOutput works for a a tree made from the file test2
 *    with no remapping. */
TEST(formatOutput, fullTree2){
        ClusterParse test = fullTree2();
    /* We are not interested in checking remapping at this point, so we 
     *     pass an empty vector as the argument to formatOutput. */  
    vector<size_t> testVector; 
    vector<size_t> result = test.formatOutput(testVector); 
    /* We get a vector to check against. */ 
    vector<size_t> checkVector = result_fullTree2();

    /* We perform a preliminary check to make sure our vectors are the
     *     same size... */ 
    assert(checkVector.size() == result.size()); 

    /* Then we check that every element in our result and the expected
     *     result are the same. */ 
    for (size_t i = 0; i < checkVector.size(); ++i){
        assert(result[i] == checkVector[i]); 
    }
}


/* Check that formatOutput works on the edge case of a large 
 *     (500 node) stick without remapping.*/ 
TEST(formatOutput, largeStick){
    ClusterParse test = largeStickTree(); 

    /* Because we don't want to remap anything, we pass an empty
     *     vector. */ 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector); 

    assert(result.size() == 1); 
    assert(result[0] == 0); 
}

/* Checks the result of formatOutput for 
 *     a larger, balanced tree. */ 
TEST(formatOutput, balancedTree){
    ClusterParse test = balancedTree(); 
    /* Again, we don't want to remap anything, so we pass
     *     an empty vector. */ 
    vector<size_t> testVector; 
    std::vector<size_t> result = test.formatOutput(testVector);

    /* Because of the way we constructed our balanced tree, 
     *     the leaves should come out consecutively.  */ 
    assert(result.size() == 8); 
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == i); 
    }
}


/* Checks the remapping capabilities of formatOutput, by remapping 
 *     to a nonconsecutive set of numbers. */ 
TEST(OutputRemap, fullTree1){
    ClusterParse test = fullTree1();

    /* We create a remapping vector that remaps everything to itself
     *    multiplied by 13. */ 
    vector<size_t> testVector; 
    for (size_t i = 0; i < 10; ++i){
        testVector.push_back(i * 13); 
    }

    /* We remap using that output.  */ 
    vector<size_t> result = test.formatOutput(testVector);
    vector<size_t> checkVector = result_fullTree1(); 
    /*  We check our remapping worked against our result_fullTree1 vector. */
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == checkVector[i] * 13); 
    }
}

/* Checks that remapping works on a nonincreasing set of numbers. */ 
TEST(OutputRemap, fullTree2){
    ClusterParse test = fullTree2();

    /* We create a remapping vector that remaps everything to 27 minus
     *    itself. */ 
    vector<size_t> testVector; 
    for (size_t i = 0; i < 11; ++i){
        testVector.push_back(27 - i); 
    }

    /* We remap using that output.  */ 
    vector<size_t> result = test.formatOutput(testVector);
    vector<size_t> checkVector = result_fullTree2(); 

    /*  We check our remapping worked against our result_fullTree2 vector. */
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == 27 - checkVector[i]); 
    }
}



/* Tests getParent on a small tree which we create within the function. */
TEST(getParent, smallTree)
{
    /* We create the tree to test on... */ 
    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    /* And test getParent on it. */ 
    assert(test.getParent(0) == 2);
    assert(test.getParent(1) == 2);
    assert(test.getParent(2) == 5); 
    assert(test.getParent(3) == 4); 
    assert(test.getParent(4) == 5); 
}


/* Test getRightChild and getLeftChild functions on a 
 *     small tree that we create within the function. */ 
TEST(getChildren, smallTree)
{
    /* We create our small tree to test on. */ 
    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    /* Test that the getChildren works on a small tree...  */ 
    assert(test.getLeftChild(2) == 0);
    assert(test.getRightChild(2) == 1);
    assert(test.getLeftChild(4) == 3); 
    assert(test.getLeftChild(5) == 2); 
    assert(test.getRightChild(5) == 4); 
}



TEST(childrenExistance, smallTree)
{
    /* We create our small tree to test on. */ 

    ClusterParse test; 
    test.insert(0, 2);
    test.insert(1, 2); 
    test.insert(2, 5);
    test.insert(3, 4);
    test.insert(4, 5); 

    /* Test that child existance functions work
     *     on a small tree. */ 

    /* First, we check on the leaves... */ 
    assert(test.leftChild(0) == false); 
    assert(test.rightChild(0) == false); 
    assert(test.rightChild(1) == false); 
    assert(test.leftChild(1) == false); 
    assert(test.leftChild(3) == false); 
    assert(test.rightChild(3) == false);

    /* Then the ones with one child... (it should be the left) */ 

    assert(test.leftChild(4) == true); 
    assert(test.rightChild(3) == false); 

    /* Then the ones with two...  */ 
    assert(test.rightChild(2) == true); 
    assert(test.leftChild(2) == true); 
    assert(test.rightChild(5) == true);
    assert(test.leftChild(5) == true); 

}
/* Tests the getParent function for the 
 *     tree generated from the test1 file. */ 
TEST(parent, fullTree1){
    /* Create the tree to test on... */ 
    ClusterParse test = fullTree1(); 
    /* And test it. */ 
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

/* Tests the isChild function for the 
 *     tree generated from the test1 file. */ 
TEST(children, fullTree1){
    /* Create the tree to test on... */ 
    ClusterParse test = fullTree1(); 
    /* And test it. */ 
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

/* Checks that getLeaves  works for a small stick with a single leaf. */
TEST(getLeaves, smallStick){
    ClusterParse test = smallStickTree();
    vector<size_t> testVector;
    size_t root = test.getRoot();
    std::vector<size_t> result = test.getLeaves(testVector, root);

    /* We check that the output of getLeaves for a stick with a
     *     single leaf is the single number that we expect. */
    assert(result.size() == 1);
    assert(result[0] == 0);
}

/* Checks that getLeaves works for a a tree made from the file test1.
 *     with no remapping. */
TEST(getLeaves, fullTree){
    ClusterParse test = fullTree1();
    /* We are not interested in checking remapping at this point, so we
     *     pass an empty vector as the argument to getLeaves. */
    vector<size_t> testVector;
    size_t root = test.getRoot();
    vector<size_t> result = test.getLeaves(testVector, root);

    /* We get a vector to check against. */
    vector<size_t> checkVector = result_fullTree1();

    /* We perform a preliminary check to make sure our vectors are the
     *     same size... */
    assert(checkVector.size() == result.size());

    /* Then we check that every element in our result and the expected
     *     result are the same. */
    for (size_t i = 0; i < checkVector.size(); ++i){
        assert(result[i] == checkVector[i]);
    }
}

/* Checks that getLeaves works for a a tree made from the file test2
 *    with no remapping. */
TEST(getLeaves, fullTree2){
        ClusterParse test = fullTree2();
    /* We are not interested in checking remapping at this point, so we
     *     pass an empty vector as the argument to getLeaves. */
    vector<size_t> testVector;
     size_t root = test.getRoot();
     vector<size_t> result = test.getLeaves(testVector, root);
    /* We get a vector to check against. */
    vector<size_t> checkVector = result_fullTree2();

    /* We perform a preliminary check to make sure our vectors are the
     *     same size... */
    assert(checkVector.size() == result.size());

    /* Then we check that every element in our result and the expected
     *     result are the same. */
    for (size_t i = 0; i < checkVector.size(); ++i){
        assert(result[i] == checkVector[i]);
    }
}


/* Check that getLeaves works on the edge case of a large
 *     (500 node) stick without remapping.*/
TEST(getLeaves, largeStick){
    ClusterParse test = largeStickTree();

    /* Because we don't want to remap anything, we pass an empty
     *     vector. */
    vector<size_t> testVector;
    size_t root = test.getRoot();
    std::vector<size_t> result = test.getLeaves(testVector, root);

    assert(result.size() == 1);
    assert(result[0] == 0);
}

/* Checks the result of formatOutput for
 *     a larger, balanced tree. */
TEST(getLeaves, balancedTree){
    ClusterParse test = balancedTree();
    /* Again, we don't want to remap anything, so we pass
     *     an empty vector. */
    vector<size_t> testVector;
    size_t root = test.getRoot();
    std::vector<size_t> result = test.getLeaves(testVector, root);

    /* Because of the way we constructed our balanced tree,
     *     the leaves should come out consecutively.  */
    assert(result.size() == 8);
    for (size_t i = 0; i < result.size(); ++i){
        assert(result[i] == i);
    }
}

TEST(formatfunctions, small)
{
    ClusterParse test;
    test.insert(0, 3);
    test.insert(1, 3);
    test.insert(3, 5);
    test.insert(2, 4);
    test.insert(4, 5);

    vector<size_t> mappingVector;
    vector<size_t> leaves;

    size_t root = test.getRoot();

    vector<size_t> vector1 = test.formatOutput(mappingVector);
    vector<size_t> vector2 = test.getLeaves(leaves, root);

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
