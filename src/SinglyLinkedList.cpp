#include "SinglyLinkedList.h"

#include <format>
#include <iostream>
#include <stdexcept>

// =============================================================================
// Given implementations — review these before working on the TODOs below.
// =============================================================================

// --- Destructor ---
//
// Temp-pointer pattern: save the current head, advance head_, delete the saved node.
// Repeats until head_ is nullptr (every node has been freed).

SinglyLinkedList::~SinglyLinkedList() {
    while (head_) {
        auto* temp = head_;
        head_      = head_->next;
        delete temp;
    }
}

// --- Insertion ---

void SinglyLinkedList::push_front(int value) {
    // O(1): new node's next points to the current head, then head moves forward.
    head_ = new Node{value, head_};
    ++size_;
}

void SinglyLinkedList::push_back(int value) {
    auto* node = new Node{value};

    if (!head_) {
        head_ = node;
    } else {
        auto* current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }

    ++size_;
}

// --- Removal ---

void SinglyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // Temp-pointer pattern: save, advance, delete.
    auto* temp = head_;
    head_      = head_->next;
    delete temp;
    --size_;
}

// --- Utility ---

void SinglyLinkedList::print() const {
    auto* current = head_;
    while (current) {
        std::cout << std::format("{} -> ", current->data);
        current = current->next;
    }
    std::cout << "nullptr\n";
}

int  SinglyLinkedList::get_size()  const noexcept { return size_; }
bool SinglyLinkedList::is_empty()  const noexcept { return size_ == 0; }

// =============================================================================
// Solutions
// =============================================================================

// --- pop_back ---

// ! DISCUSSION: pop_back must FIND the last node before it can delete it.
//   Singly-linked nodes only know their SUCCESSOR (node->next), so once we
//   reach the last node we have no way to go back to the one before it.
//
//   The trailing pointer pattern solves this with two pointers:
//     'previous' — one step behind 'current' at all times
//     'current'  — advances to the last node
//   When the loop ends, 'current' is the last node and 'previous' is the
//   second-to-last — the one whose next_ we need to set to nullptr.
//
// ! DISCUSSION: pop_back is O(n). Every call walks the entire list just to
//   remove one node. Compare this to pop_front which is O(1) — it just
//   moves the head pointer. This asymmetry is a fundamental weakness of
//   singly linked lists.
//   Doubly linked lists fix it with a prev pointer — O(1) pop_back
//   using a tail_ member. We'll build that in CT9.
//
// ? SEE DIAGRAM: images/svgs/pop_back.svg

void SinglyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // ! DISCUSSION: Single-node case — head IS the tail.
    //   If head_->next is nullptr there is no second-to-last node.
    //   We skip the trailing pointer entirely: just delete head_ and reset.
    if (!head_->next) {
        delete head_;
        head_ = nullptr;
        --size_;
        return;
    }

    // ! DISCUSSION: Set up the trailing pointer pair.
    //   Both start near the front of the list, then advance together
    //   until 'current' reaches the last node.
    auto* previous = head_;
    auto* current  = head_->next;

    // ! DISCUSSION: Advance until current has no successor (it IS the last node).
    //   Each iteration: step previous up to current, then step current forward.
    //   After the loop: current == last node, previous == second-to-last.
    while (current->next) {
        previous = current;
        current  = current->next;
    }

    // ! DISCUSSION: Unlink and delete the last node.
    //   previous->next = nullptr  — previous is now the new tail
    //   delete current            — free the old tail's memory
    previous->next = nullptr;
    delete current;
    --size_;
}

// --- contains ---

// ! DISCUSSION: contains() is a read-only search — it traverses without modifying.
//   Walk from head_ to nullptr. If any node's data matches, return true immediately.
//   If we reach nullptr without a match, return false.
//
// ! DISCUSSION: O(n) in the worst case. For an unsorted list there's no shortcut —
//   every node might need to be inspected. If the list were sorted we could
//   stop early (value < current means it can't be further right), but we're
//   not maintaining sorted order here.
//
// ! DISCUSSION: Notice the 'const' qualifier. contains() promises not to
//   modify the list. The compiler enforces this — only const methods may be
//   called on a const object or through a const reference.

bool SinglyLinkedList::contains(int value) const {
    // ! DISCUSSION: One pointer is enough here — we're only reading.
    //   No trailing pointer needed because we never modify next_ pointers.
    auto* current = head_;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

// --- remove ---

// ! DISCUSSION: remove() deletes the FIRST node whose data matches value.
//   If the value isn't in the list, do nothing (no error).
//
// ! DISCUSSION: Three cases, each needing different treatment:
//   1. Empty list        — nothing to do; guard at the top handles this.
//   2. Head node matches — there is no 'previous' node to update.
//                          Delegate to pop_front(); it handles memory and size_.
//   3. Middle/tail match — trailing pointer to locate and unlink the node.
//
// ! DISCUSSION: The trailing pointer logic is identical to pop_back, except
//   instead of advancing unconditionally to the end, we stop when we FIND
//   a match. The pointer surgery is the same:
//     previous->next = current->next   (skip over current)
//     delete current                   (free the memory)
//     --size_

void SinglyLinkedList::remove(int value) {
    if (!head_) return;

    // ! DISCUSSION: Special case — the head node is the match.
    //   The trailing pointer pattern requires a 'previous' node, but there
    //   is no node before head_. Instead, delegate to pop_front().
    if (head_->data == value) {
        pop_front();
        return;
    }

    // ! DISCUSSION: Set up the trailing pointer pair.
    //   We already know head_ is not the match, so 'previous' starts at
    //   head_ and 'current' starts one step ahead at head_->next.
    auto* previous = head_;
    auto* current  = head_->next;

    while (current) {
        if (current->data == value) {
            previous->next = current->next;
            delete current;
            --size_;
            return;
        }
        previous = current;
        current  = current->next;
    }
}
