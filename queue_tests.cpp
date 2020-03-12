// FILE: queue_tests.cpp
// CS 223 Winter 2018, Lab 5
//
// <Name and Date>
//

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"  // declares the testing framework
#include "queue.h"

#define BACKWARD_HAS_DW 1
#include "backward.hpp"
backward::SignalHandling sh;

using namespace std;
using namespace cs223_lab5;

namespace
{
// Lab 5 Unit Testing Plan -- 28 tests, 19 of which are provided

// 3 tests for BasicConstructor, size, is_empty
//   - PRVD_DefaultConstructor
//   - PRVD_Capacity_2
//   - PRVD_Capacity_20

// 8 tests for Front, Push, Pop
//   - PRVD_pushOneItemCheckFront
//   - PRVD_pushTwoItemsCheckFront
//   - PRVD_pushTwoPopOneCheckFront
//   - STU_pushTwoPopTwoCheckEmpty              <<< MUST PROVIDE
//   - STU_pushTwoPopOnePushTwoPopOnePushThree  <<< MUST PROVIDE
//   - STU_pushThreePopTwoPushTwo               <<< MUST PROVIDE
//   - STU_pushThreePopTwoPushThree             <<< MUST PROVIDE
//   - STU_startCapacityTwoPushTwelvePopTen     <<< MUST PROVIDE

// 6 tests for Equivalence & Inequivalence
//   - PRVD_nonempty_queue_equivalent_to_itself
//   - PRVD_empty_equivalent_to_empty
//   - PRVD_empty_vs_nonempty
//   - PRVD_both_nonempty_different_lengths
//   - PRVD_both_nonempty_same_lengths_not_equiv
//   - PRVD_both_nonempty_same_values_equiv

// 6 tests for Assignment Operator
//   - PRVD_selfAssignmentIsOK
//   - PRVD_copyFromEmptytoNonemptyANDcopyIsIndependent
//   - PRVD_copyFromNonemptyToEmptyANDcopyIsIndependent
//   - PRVD_copyFromQueueWithThreeItemsAtIndexCapMinusOneToEmptyQueue
//   - PRVD_copyFromQueueWithFourItemsAndCapacityFourToQueueSizeSix
//   - PRVD_copyFromLongQueueToQueueSizeFive

// 5 tests for Copy Constructor
//   - PRVD_copyEmptyANDcopyIsIndependent
//   - PRVD_copyOneItemANDcopyIsIndependent
//   - PRVD_copyThreeItemsAtIndexCapMinusOne
//   - PRVD_copyFourItemsFromCapacityFour
//   - PRVD_copyLongQueue

TEST(PRVD_TestBasicConstructorANDaccessorFunctions, DefaultConstructor)
{
    queue q1;  // empty queue, capacity 8
    EXPECT_TRUE(q1.is_empty());
    EXPECT_EQ(q1.size(), 0);
}

TEST(PRVD_TestBasicConstructorANDaccessorFunctions, Capacity_2)
{
    queue q1(2);  // empty queue, capacity 2
    EXPECT_TRUE(q1.is_empty());
    EXPECT_EQ(q1.size(), 0);
}

TEST(PRVD_TestBasicConstructorANDaccessorFunctions, Capacity_20)
{
    queue q1(20);  // empty queue, capacity 20
    EXPECT_TRUE(q1.is_empty());
    EXPECT_EQ(q1.size(), 0);
}

// Next we implement and test:
//  - ensure_capacity (do not test directly)
//  - front
//  - push
//  - pop

TEST(PRVD_TestFrontPushPop, pushOneItemCheckFront)
{
    queue q1;  // empty queue, capacity 8
    q1.push("ziggy");
    EXPECT_EQ(q1.front(), "ziggy");
    EXPECT_EQ(q1.size(), 1);
    EXPECT_FALSE(q1.is_empty());
}

TEST(PRVD_TestFrontPushPop, pushTwoItemsCheckFront)
{
    queue q1;  // empty queue, capacity 8
    q1.push("ziggy");
    q1.push("cleo");
    EXPECT_EQ(q1.front(), "ziggy");
    EXPECT_EQ(q1.size(), 2);
}

TEST(PRVD_TestFrontPushPop, pushTwoPopOneCheckFront)
{
    queue q1;  // empty queue, capacity 8
    q1.push("ziggy");
    q1.push("cleo");
    q1.pop();
    EXPECT_EQ(q1.front(), "cleo");
    EXPECT_EQ(q1.size(), 1);
}

TEST(PRVD_TestFrontPushPop, STU_pushTwoPopTwoCheckEmpty)
{
    cout << "Test needs to be implemented" << endl;
}

TEST(PRVD_TestFrontPushPop, STU_pushTwoPopOnePushTwoPopOnePushThree)
{
    cout << "Test needs to be implemented" << endl;
}

// this test forces next_index to wrap around the end of the array
TEST(PRVD_TestFrontPushPop, STU_pushThreePopTwoPushTwo)
{
    cout << "Test needs to be implemented" << endl;
}

// forces ensure_capacity to enlarge the array
TEST(PRVD_TestFrontPushPop, STU_pushThreePopTwoPushThree)
{
    cout << "Test needs to be implemented" << endl;
}

// force a lot of array enlarging and wrapping around the end of the array
TEST(PRVD_TestFrontPushPop, STU_startCapacityTwoPushTwelvePopTen)
{
    cout << "Test needs to be implemented" << endl;
}

// Now we write tests for iterators
TEST(PRVD_TestIterator, beginAndDereference)
{
    queue q(4);
    q.push("a");
    q.push("b");
    q.push("c");
    q.pop();
    auto iter = q.begin();
    EXPECT_EQ(*iter, "b");
}

TEST(PRVD_TestIterator, increment)
{
    queue q(4);
    q.push("a");
    q.push("b");
    q.push("c");
    q.pop();
    q.push("d");
    auto iter = q.begin();
    EXPECT_EQ(*iter, "b");
    ++iter;
    EXPECT_EQ(*iter, "c");
    ++iter;
    EXPECT_EQ(*iter, "d");
}

TEST(PRVD_TestIterator, assignViaIterator)
{
    queue q(4);
    q.push("a");
    q.push("b");
    q.push("c");
    q.pop();
    q.push("d");
    auto iter = q.begin();
    ASSERT_EQ(*iter, "b");
    ++iter;
    *iter = "e";
    EXPECT_EQ(*iter, "e");
    EXPECT_EQ(*q.begin(), "b");
    EXPECT_EQ(*(++q.begin()), "e");
}

TEST(PRVD_TestIterator, endAndEquivalence)
{
    queue q(4);
    q.push("a");
    q.push("b");
    q.push("c");
    q.pop();
    q.push("d");
    EXPECT_NE(q.begin(), q.end());
    auto iter = q.begin();
    ASSERT_EQ(*iter, "b");
    EXPECT_EQ(iter, q.begin());
    ++iter;  // c
    EXPECT_NE(iter, q.begin());
    EXPECT_NE(iter, q.end());
    ++iter;  // d
    EXPECT_NE(iter, q.begin());
    EXPECT_NE(iter, q.end());
    ++iter;
    EXPECT_NE(iter, q.begin());
    EXPECT_EQ(iter, q.end());
}

TEST(PRVD_TestIterator, iteratorLoop)
{
    queue q(4);
    q.push("a");
    q.push("b");
    q.push("c");
    q.pop();
    q.pop();
    q.push("d");
    q.push("e");
    stringstream s;
    for (auto iter = q.begin(); iter != q.end(); ++iter)
    {
        s << *iter;
    }
    EXPECT_EQ(s.str(), "cde");
}

// Next we implement and test:
//  equivalence
//  inequivalence
TEST(PRVD_TestEquivalenceInequivalence, nonempty_queue_equivalent_to_itself)
{
    queue q;
    q.push("a");
    EXPECT_TRUE(q == q);
    EXPECT_FALSE(q != q);
}

TEST(PRVD_TestEquivalenceInequivalence, empty_equivalent_to_empty)
{
    queue q;
    EXPECT_TRUE(q == q);
    EXPECT_FALSE(q != q);
}

TEST(PRVD_TestEquivalenceInequivalence, empty_vs_nonempty)
{
    queue q1;
    queue q2;
    q2.push("b");
    EXPECT_FALSE(q1 == q2);
    EXPECT_TRUE(q1 != q2);
}

TEST(PRVD_TestEquivalenceInequivalence, both_nonempty_different_lengths)
{
    queue q1;
    queue q2;
    q1.push("a");
    q1.push("b");
    q2.push("a");
    EXPECT_FALSE(q1 == q2);
    EXPECT_TRUE(q1 != q2);
}

TEST(PRVD_TestEquivalenceInequivalence, both_nonempty_same_lengths_not_equiv)
{
    queue q1;
    q1.push("July 4");
    q1.push("Labor Day");
    q1.push("Halloween");
    q1.push("Thanksgiving");
    queue q2;
    q2.push("July 4");
    q2.push("Labor Day");
    q2.push("Halloween");
    q2.push("Veterans' Day");
    EXPECT_FALSE(q1 == q2);
    EXPECT_TRUE(q1 != q2);
    EXPECT_FALSE(q2 == q1);
    EXPECT_TRUE(q2 != q1);
}

TEST(PRVD_TestEquivalenceInequivalence, both_nonempty_same_values_equiv)
{
    queue q1;
    q1.push("July 4");
    q1.push("July 4");
    q1.push("July 4");
    q1.pop();
    q1.pop();
    q1.push("Labor Day");
    q1.push("Halloween");
    q1.push("Thanksgiving");
    queue q2;
    q2.push("July 4");
    q2.push("Labor Day");
    q2.push("Halloween");
    q2.push("Thanksgiving");
    EXPECT_TRUE(q1 == q2);
    EXPECT_FALSE(q1 != q2);
    EXPECT_TRUE(q2 == q1);
    EXPECT_FALSE(q2 != q1);
}

// Finally, we implement and test:
//  assignment
//  copy constructor
//  destructor (test indirectly, with Valgrind)
TEST(PRVD_TestAssignmentOperator, selfAssignmentIsOK)
{
    queue q1(2);
    q1.push("a");
    q1.push("b");
    q1.pop();
    q1 = q1;
    EXPECT_EQ(q1.size(), 1);
    EXPECT_EQ(q1.front(), "b");
}

TEST(PRVD_TestAssignmentOperator, copyFromEmptytoNonemptyANDcopyIsIndependent)
{
    queue q1;
    q1.push("a");
    queue q2;
    q1 = q2;
    EXPECT_TRUE(q1.is_empty());
    q2.push("c");
    EXPECT_TRUE(q1.is_empty());
}

TEST(PRVD_TestAssignmentOperator, copyFromNonemptyToEmptyANDcopyIsIndependent)
{
    queue q1(3);
    q1.push("a");
    q1.push("b");
    queue q2(1);
    q2 = q1;
    EXPECT_EQ(q2.size(), 2);
    q1.push("c");
    EXPECT_EQ(q2.size(), 2);
}

TEST(PRVD_TestAssignmentOperator,
     copyFromQueueWithThreeItemsAtIndexCapMinusOneToEmptyQueue)
{
    queue q1(4);  // empty queue size 4
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.pop();
    q1.pop();
    q1.pop();
    q1.push("they");
    q1.push("say");
    queue q2;
    q2 = q1;
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), "hey");
    q2.pop();
    EXPECT_EQ(q2.front(), "they");
    q2.pop();
    EXPECT_EQ(q2.front(), "say");
}

TEST(PRVD_TestAssignmentOperator,
     copyFromQueueWithFourItemsAndCapacityFourToQueueSizeSix)
{
    queue q1(4);  // empty queue size 4
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.pop();
    q1.pop();
    q1.pop();
    q1.push("they");
    q1.push("say");
    q1.push("stay");  // hey, they, say, stay
    queue q2;
    q2.push("hey");
    q2.push("hey");
    q2.push("hey");
    q2.push("hey");
    q2.push("hey");
    q2.push("hey");
    q2 = q1;
    string correct("queue of size 4:\nhey\nthey\nsay\nstay\n");
    stringstream actual;
    actual << q2;
    EXPECT_EQ(actual.str(), correct);
}

TEST(PRVD_TestAssignmentOperator, copyFromLongQueueToQueueSizeFive)
{
    queue q1(10);  // empty queue, capacity 10
    q1.push("a");
    q1.push("b");
    q1.push("c");
    q1.push("d");
    q1.push("e");
    q1.push("f");
    q1.push("g");
    q1.push("h");
    q1.push("i");
    q1.push("j");
    queue q2;
    for (int i = 0; i < 5; i++) q2.push("hey");
    ASSERT_EQ(q2.size(), 5);
    q2 = q1;
    EXPECT_EQ(q2.size(), 10);
    string correct("queue of size 10:\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\n");
    stringstream actual;
    actual << q2;
    EXPECT_EQ(actual.str(), correct);
}

TEST(PRVD_TestCopyConstructor, copyEmptyANDcopyIsIndependent)
{
    queue q1(3);
    queue q2(q1);
    q1.push("a");
    EXPECT_TRUE(q2.is_empty());
}

TEST(PRVD_TestCopyConstructor, copyOneItemANDcopyIsIndependent)
{
    queue q1(3);
    q1.push("a");
    queue q2(q1);
    q1.push("b");
    EXPECT_EQ(q2.size(), 1);
}

TEST(PRVD_TestCopyConstructor, copyThreeItemsAtIndexCapMinusOne)
{
    queue q1(4);  // empty queue size 4
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.pop();
    q1.pop();
    q1.pop();
    q1.push("they");
    q1.push("say");
    queue q2(q1);  // hey, they, say
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), "hey");
    q2.pop();
    EXPECT_EQ(q2.front(), "they");
    q2.pop();
    EXPECT_EQ(q2.front(), "say");
}

TEST(PRVD_TestCopyConstructor, copyFourItemsFromCapacityFour)
{
    queue q1(4);  // empty queue size 4
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.push("hey");
    q1.pop();
    q1.pop();
    q1.pop();
    q1.push("they");
    q1.push("say");
    q1.push("stay");  // hey, they, say, stay
    queue q2(q1);
    string correct("queue of size 4:\nhey\nthey\nsay\nstay\n");
    stringstream actual;
    actual << q2;
    EXPECT_EQ(actual.str(), correct);
}

TEST(PRVD_TestCopyConstructor, copyLongQueue)
{
    queue q1(10);  // empty queue, capacity 10
    q1.push("a");
    q1.push("b");
    q1.push("c");
    q1.push("d");
    q1.push("e");
    q1.push("f");
    q1.push("g");
    q1.push("h");
    q1.push("i");
    q1.push("j");
    queue q2(q1);
    EXPECT_EQ(q2.size(), 10);
    string correct("queue of size 10:\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\n");
    stringstream actual;
    actual << q2;
    EXPECT_EQ(actual.str(), correct);
}

}  // end namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
