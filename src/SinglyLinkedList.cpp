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

    // ! DISCUSSION: The trailing pointer pattern.
    //   'previous' starts at head_, 'current' starts one step ahead.
    //   When the loop ends, current is at the last node and previous
    //   is at the second-to-last — the node whose next we set to nullptr.
    //
    // ! DISCUSSION: pop_back is O(n) — we must walk the whole list to find
    //   the second-to-last node. pop_front is O(1). This asymmetry is a
    //   key weakness of singly linked lists. A doubly linked list (CT9)
    //   fixes it with a tail_ pointer.
    auto* previous = head_;
    auto* current  = head_->next;
    while (current->next) {
        previous = current;
        current  = current->next;
    }

    previous->next = nullptr;
    delete current;
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
// TODO sections — implement the two methods below.
// =============================================================================

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

    // TODO: Create a 'current' pointer starting at head_

    // TODO: While current is not nullptr:
    //         If current->data equals value, return true.
    //         Advance current to current->next.

    // TODO: Return false — reached nullptr without finding value

    return false; // placeholder — remove this line when done
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
// ! DISCUSSION: The trailing pointer logic here is the same pattern as pop_back,
//   except instead of advancing unconditionally to the end, we stop when we
//   FIND a match. The pointer surgery is the same:
//     previous->next = current->next   (skip over current)
//     delete current                   (free the memory)
//     --size_

void SinglyLinkedList::remove(int value) {
    if (!head_) return;

    // ! DISCUSSION: Special case — the head node is the match.
    //   The trailing pointer pattern requires a 'previous' node, but there
    //   is no node before head_. Instead, delegate to pop_front().
    if (head_->data == value) {
        // TODO: Call pop_front() to remove the head node

        return;
    }

    // ! DISCUSSION: Set up the trailing pointer pair.
    //   We already know head_ is not the match, so 'previous' starts at
    //   head_ and 'current' starts one step ahead at head_->next.

    // TODO: Create 'previous' pointing to head_, and 'current' pointing to head_->next

    // TODO: While current is not nullptr:
    //         If current->data == value:
    //           Set previous->next = current->next   (bypass current)
    //           Delete current
    //           Decrement size_
    //           Return
    //         Otherwise:
    //           Advance previous to current
    //           Advance current to current->next
}
