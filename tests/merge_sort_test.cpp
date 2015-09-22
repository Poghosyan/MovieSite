#include "gtest/gtest.h"
#include "mergesort.h"
#include <vector>
#include <iostream>

class MergeSortTest: public ::testing::Test
{
protected:
	MergeSortTest()
	{
		// You can do set-up work for each test here.
	}

	virtual ~MergeSortTest()
	{
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	std::vector<int> unsorted;
	MergeSort merge;
};

TEST (MergeSortTest, BasicCase) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(5);
  v.push_back(3);
  v.push_back(2);
  v.push_back(4);
  std::vector<int> v_sorted = MergeSort::sort(v);
  for(int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v_sorted.at(i), i + 1);
  }
}

TEST (MergeSortTest, MultipleSame) {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(2);
	v.push_back(2);
	v.push_back(4);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	std::vector<int> v_sorted = MergeSort::sort(v);
  	for(int i = 0; i < v.size(); i++) {
    	EXPECT_TRUE(v_sorted[i] <= v_sorted[i+1]);
  	}
}

TEST (MergeSortTest, BigDifference) {
	
}
