#include "gtest/gtest.h"
#include "set.h"

class SetTest : public ::testing::Test {
protected:
	SetTest () : letters(Set<int>()), symbols(Set<int>()) {
	}

	~SetTest () {

	}

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
		for(int i = 0; i < 26; ++i) {
			letters.add(i);
		}
		for(int i = 8; i < 32; ++i) {
			symbols.add(i);
		}
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	Set<int> letters, symbols;
};

TEST_F (SetTest, unionTest) {
	std::cout << "Size of letters " << letters.size() << " size of symbols " << symbols.size() <<std::endl;
	Set<int> unionSet = letters.setUnion(symbols);
	for (Set<int>::Iterator it = letters.begin(); it != letters.end(); ++it)
	{
		bool asses = unionSet.contains(*it);
 		EXPECT_TRUE(asses) << " " << asses;
	}
	for (Set<int>::Iterator it = symbols.begin(); it != symbols.end(); ++it)
	{
		EXPECT_TRUE(unionSet.contains(*it));
	}
}

TEST_F (SetTest, intersectionTest) {
	std::cout << "Size of letters " << letters.size() << " size of symbols " << symbols.size() <<std::endl;
	Set<int> interSet = letters.setIntersection(symbols);
	for (int i = 8; i < 25; ++i)
	{
		bool asses = interSet.contains(i);
 		EXPECT_TRUE(asses) << " " << asses;
	}
}