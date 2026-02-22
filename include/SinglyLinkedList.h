#pragma once
#include "Node.h"

class SinglyLinkedList {
public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList();

    // Rule of 5: copying and moving are disabled
    SinglyLinkedList(const SinglyLinkedList&)            = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    SinglyLinkedList(SinglyLinkedList&&)                 = delete;
    SinglyLinkedList& operator=(SinglyLinkedList&&)      = delete;

    // Insertion
    void push_front(int value);   // O(1)
    void push_back(int value);    // O(n)

    // Removal
    void pop_front();             // O(1)
    void pop_back();              // O(n) — trailing pointer pattern

    // Search & remove by value
    bool contains(int value) const;  // O(n)
    void remove(int value);          // O(n)

    // Accessors
    int  get_size()  const noexcept;
    bool is_empty()  const noexcept;

    // Utility
    void print() const;

private:
    Node* head_ = nullptr;
    int   size_ = 0;
};
