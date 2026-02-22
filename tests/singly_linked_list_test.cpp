#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "SinglyLinkedList.h"

static std::string capturePrint(const SinglyLinkedList& list) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.print();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== pop_back Tests (10 points) ====================

TEST(SinglyLinkedListTest, PopBackRemovesTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, PopBackToEmpty) {
    SinglyLinkedList list;
    list.push_front(10);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(SinglyLinkedListTest, PopBackSingleNode) {
    SinglyLinkedList list;
    list.push_back(42);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_TRUE(capturePrint(list).find("nullptr") != std::string::npos);
}

// ==================== contains() Tests (9 points) ====================

TEST(SinglyLinkedListTest, ContainsTrueForHeadMiddleTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(30));
}

TEST(SinglyLinkedListTest, ContainsFalseForMissingValue) {
    SinglyLinkedList list;
    list.push_back(10);
    EXPECT_FALSE(list.contains(99));
}

TEST(SinglyLinkedListTest, ContainsOnEmptyList) {
    SinglyLinkedList list;
    EXPECT_FALSE(list.contains(1));
}

// ==================== remove() Tests (9 points) ====================

TEST(SinglyLinkedListTest, RemoveTail) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(30);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 20 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveMiddle) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("10 -> 30 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveHead) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(10);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(capturePrint(list).find("20 -> 30 -> nullptr") != std::string::npos);
}

TEST(SinglyLinkedListTest, RemoveNotFound) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.remove(99);
    EXPECT_EQ(list.get_size(), 2);
}

TEST(SinglyLinkedListTest, RemoveOnEmptyList) {
    SinglyLinkedList list;
    EXPECT_NO_THROW(list.remove(5));
}
