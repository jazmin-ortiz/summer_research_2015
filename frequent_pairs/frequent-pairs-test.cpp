/**
 * \file frequent-pairs-test.cpp
 *
 * \Authors Jazmin Ortiz
 *
 * \brief Tests a FrequentPairs for correctness
 */

#include "FrequentPairs.hpp"
#include "gtest/gtest.h"

#include <memory>

using namespace std;

//--------------------------------------------------
//           TEST FUNCTIONS
//--------------------------------------------------

TEST(constructor, default_constructor)
{
    FrequentPairs test;
    vector<size_t>& test_sequence = test.get_Sequence();
    unordered_map<size_t,size_t>& test_Table = test.get_FrequentLBAsTable();
    vector<size_t>& test_FreqLBAs = test.get_FrequentLBAs();

    // Make sure that all data members when default constructed contain no
    // elements.
    assert(test_sequence.empty());
    assert(test_FreqLBAs.empty());

    assert(test_Table.size() == 0);

}

TEST(insert_LBA_into_Sequence, one)
{

    FrequentPairs test;

    test.insert_LBA_into_Sequence("1");

    vector<size_t>& test_sequence = test.get_Sequence();

    assert(test_sequence.size() == 1);
    assert(test_sequence[0] == 1);
}

TEST(insert_LBA_into_Sequence, large_all_same)
{

    FrequentPairs test;

    // insert 500 of the same character
    for (size_t i = 0; i < 500; ++i) {
        test.insert_LBA_into_Sequence("1");
    }

    vector<size_t>& test_sequence = test.get_Sequence();

    for (size_t i = 0; i < 500; ++i) {

        assert(test_sequence[i] == 1);

    }

    assert(test_sequence.size() == 500);
}


TEST(insert_LBA_into_Sequence, large_consectuive)
{

    FrequentPairs test;

    // insert 500 of the same character
    string s;
    for (size_t i = 0; i < 500; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);
    }

    vector<size_t>& test_sequence = test.get_Sequence();

    for (size_t i = 0; i < 500; ++i) {

        assert(test_sequence[i] == i);

    }

    assert(test_sequence.size() == 500);

}

TEST(insert_LBA_into_Sequence, large_non_consecutive)
{

       FrequentPairs test;

    // insert 500 characters
    string s;
    size_t value;
    for (size_t i = 0; i < 500; ++i) {
        value = 2*1;
        s = to_string(value);
        test.insert_LBA_into_Sequence(s);
    }

    vector<size_t>& test_sequence = test.get_Sequence();

    for (size_t i = 0; i < 500; ++i) {

        assert(test_sequence[i] == 2*1);

    }

    assert(test_sequence.size() == 500);

}

TEST(insert_Frequent_LBA, one)
{

    FrequentPairs test;

    test.insert_Frequent_LBA("1");

    unordered_map<size_t, size_t>& test_table = test.get_FrequentLBAsTable();
    vector<size_t>& test_freqLBAs = test.get_FrequentLBAs();

    size_t tables_value;
    unordered_map<size_t, size_t>::iterator it = test_table.find(1);
    tables_value = it->second;

    assert(test_freqLBAs.size() == 1);
    assert(test_freqLBAs[0] == 1);

    assert(test_table.size() == 1);
    assert(tables_value == 0);
}

TEST(insert_Frequent_LBA, large_consecutive)
{

    FrequentPairs test;
    string s;
    for (size_t i = 0; i < 500; ++i) {

        s = to_string(i);
        test.insert_Frequent_LBA(s);

    }
    unordered_map<size_t, size_t>& test_table = test.get_FrequentLBAsTable();
    vector<size_t>& test_freqLBAs = test.get_FrequentLBAs();

    size_t tables_value;
    unordered_map<size_t, size_t>::iterator it;

    for (size_t i = 0; i < 500; ++i) {

        it = test_table.find(i);
        tables_value = it->second;

        assert(test_freqLBAs[i] == i);
        assert(tables_value == i);

    }

    assert(test_freqLBAs.size() == 500);
    assert(test_table.size() == 500);

}

TEST(insert_Frequent_LBA, large_non_consecutive)
{

    FrequentPairs test;
    string s;
    size_t value;
    for (size_t i = 0; i < 500; ++i) {

        value = 2*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    unordered_map<size_t, size_t>& test_table = test.get_FrequentLBAsTable();
    vector<size_t>& test_freqLBAs = test.get_FrequentLBAs();

    size_t tables_value;
    unordered_map<size_t, size_t>::iterator it;

    for (size_t i = 0; i < 500; ++i) {

        it = test_table.find(2*i);
        tables_value = it->second;

        assert(test_freqLBAs[i] == 2*i);
        assert(tables_value == i);

    }

    assert(test_freqLBAs.size() == 500);
    assert(test_table.size() == 500);

}

TEST(insert_Frequent_LBA, opposite_order)
{

    FrequentPairs test;
    string s;
    size_t value;
    for (size_t i = 0; i < 500; ++i) {

        value = 500 - i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    unordered_map<size_t, size_t>& test_table = test.get_FrequentLBAsTable();
    vector<size_t>& test_freqLBAs = test.get_FrequentLBAs();

    size_t tables_value;
    unordered_map<size_t, size_t>::iterator it;

    for (size_t i = 0; i < 500; ++i) {

        it = test_table.find(500-i);
        tables_value = it->second;

        assert(test_freqLBAs[i] == 500-i);
        assert(tables_value == i);

    }

    assert(test_freqLBAs.size() == 500);
    assert(test_table.size() == 500);

}

TEST(fillInFrequentMatrix, small_no_adjacent_frequent_LBAs)
{

    FrequentPairs test;
    string s;
    size_t value;

    // Insert LBAs in Sequence_.
    for (size_t i = 0; i < 25; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);

    }

    // Insert LBAs that were in Sequence_ into FrequentLBAs_ and
    // FrequentLBAsTable_
    for (size_t i = 0; i < 5; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    vector< vector<size_t> > adjacency_matrix = test.fillInFrequentMatrix();

    // Make sure all rows and cols are the correct size
    assert(adjacency_matrix.size() == 5);
    for (size_t i = 0; i < 5; ++i) {

        assert(adjacency_matrix[i].size() == 5);

    }

    // Make sure that all the indice's size_ts are equal to 0 since there are no
    // consecutive occurences of frequent LBAs in adjacency_matrix.
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {

            assert(adjacency_matrix[i][j] == 0);

        }
    }

}

TEST(fillInFrequentMatrix, large_no_adjacent_frequent_LBAs)
{

    FrequentPairs test;
    string s;
    size_t value;

    // Insert LBAs in Sequence_.
    for (size_t i = 0; i < 1000; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);

    }

    // Insert LBAs that were in Sequence_ into FrequentLBAs_ and
    // FrequentLBAsTable_
    for (size_t i = 0; i < 200; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    vector< vector<size_t> > adjacency_matrix = test.fillInFrequentMatrix();

    // Make sure all rows and cols are the correct size
    assert(adjacency_matrix.size() == 200);
    for (size_t i = 0; i < 200; ++i) {

        assert(adjacency_matrix[i].size() == 200);

    }

    // Make sure that all the indice's size_ts are equal to 0 since there are no
    // consecutive occurences of frequent LBAs in adjacency_matrix.
    for (size_t i = 0; i < 200; ++i) {
        for (size_t j = 0; j < 200; ++j) {

            assert(adjacency_matrix[i][j] == 0);

        }
    }

}



TEST(fillInFrequentMatrix, frequent_LBAs_adjacent_only_to_themselves)
{

    FrequentPairs test;
    string s;
    size_t value;

    // Insert each LBA into Sequence_ three times right after one another.
    for (size_t i = 0; i < 25; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);

    }

    // Insert LBAs that were in Sequence_ into FrequentLBAs_ and
    // FrequentLBAsTable_
    for (size_t i = 0; i < 5; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    vector< vector<size_t> > adjacency_matrix = test.fillInFrequentMatrix();

    // Make sure all rows and cols are the correct size
    assert(adjacency_matrix.size() == 5);
    for (size_t i = 0; i < 5; ++i) {

        assert(adjacency_matrix[i].size() == 5);

    }

    // Make sure that all the indice's size_ts are equal to 0 except when i = j
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {

            if (i == j) {

                assert(adjacency_matrix[i][j] == 2);
            } else {

                assert(adjacency_matrix[i][j] == 0);

            }

        }

    }

}

TEST(fillInFrequentMatrix, frequent_LBAs_adjacent_only_to_themselves_large)
{

    FrequentPairs test;
    string s;
    size_t value;

    // Insert each LBA into Sequence_ five times right after one another.
    for (size_t i = 0; i < 1000; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);

    }

    // Insert LBAs that were in Sequence_ into FrequentLBAs_ and
    // FrequentLBAsTable_
    for (size_t i = 0; i < 200; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    vector< vector<size_t> > adjacency_matrix = test.fillInFrequentMatrix();

    // Make sure all rows and cols are the correct size
    assert(adjacency_matrix.size() == 200);
    for (size_t i = 0; i < 200; ++i) {

        assert(adjacency_matrix[i].size() == 200);

    }

    // Make sure that all the indice's size_ts are equal to 0 except when i = j
    for (size_t i = 0; i < 200; ++i) {
        for (size_t j = 0; j < 200; ++j) {

            if (i == j) {

                assert(adjacency_matrix[i][j] == 4);
            } else {

                assert(adjacency_matrix[i][j] == 0);

            }

        }

    }

}

TEST(fillInFrequentMatrix, frequent_LBAs_adjacent_large)
{

    FrequentPairs test;
    string s;
    size_t value;

    // Insert each LBA into Sequence_ five times right after one another.
    for (size_t i = 0; i < 1000; ++i) {

        s = to_string(i);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);
        test.insert_LBA_into_Sequence(s);

    }

    /// Insert the LBAs which will be considered frequent LBAs one after the
    // other at the end, the LBAs will be inserted in the same order as they are
    // indexed in FrequentLBAs_
    for (size_t i = 0; i < 200; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_LBA_into_Sequence(s);


    }

    // Insert LBAs that were in Sequence_ into FrequentLBAs_ and
    // FrequentLBAsTable_
    for (size_t i = 0; i < 200; ++i) {

        value = 5*i;
        s = to_string(value);
        test.insert_Frequent_LBA(s);

    }

    vector< vector<size_t> > adjacency_matrix = test.fillInFrequentMatrix();

    // Make sure all rows and cols are the correct size
    assert(adjacency_matrix.size() == 200);
    for (size_t i = 0; i < 200; ++i) {

        assert(adjacency_matrix[i].size() == 200);

    }

    for (size_t i = 0; i < 200; ++i) {
        for (size_t j = 0; j < 200; ++j) {

            if (i == j) {

                assert(adjacency_matrix[i][j] == 4);

            }

            else if (i+1 == j || i == j+1) {

                assert(adjacency_matrix[i][j] == 1);

            } else {

                assert(adjacency_matrix[i][j] == 0);

            }

        }

    }

}





//--------------------------------------------------
//           RUNNING THE TESTS
//--------------------------------------------------

/// Run tests
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

