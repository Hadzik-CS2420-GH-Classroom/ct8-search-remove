#include "SinglyLinkedList.h"

#include <format>
#include <iostream>

int main() {
    std::cout << "=== Code-Together 8: Search & Remove — Farr's Ice Cream ===\n\n";

    // ! DISCUSSION: Farr's Ice Cream now accepts pre-orders by order ID.
    //   Customers submit their order ahead of time and join a queue.
    //   The manager needs three operations that CT7 left as stubs:
    //     pop_back  — the last customer in line cancels
    //     contains  — check whether an order ID is still in the queue
    //     remove    — cancel a specific order from anywhere in the queue

    // =========================================================================
    // PART 1 — pop_back: last order cancelled
    // =========================================================================

    std::cout << "=== Part 1: Pre-Order Queue ===\n\n";

    SinglyLinkedList orders;

    // --- 1. Orders arrive ---
    std::cout << "--- Orders arriving ---\n";
    orders.push_back(2001);
    orders.push_back(2002);
    orders.push_back(2003);
    orders.push_back(2004);
    orders.push_back(2005);

    std::cout << "Order queue:    ";
    orders.print();
    std::cout << std::format("Orders pending: {}\n\n", orders.get_size());

    // --- 2. Last customer changes their mind ---
    std::cout << "--- Last order cancelled ---\n";
    std::cout << "Order 2005 called in — they got impatient and left the queue.\n";

    // TODO: Call pop_back() to remove the last order

    std::cout << "Order queue:    ";
    orders.print();
    std::cout << std::format("Orders pending: {}\n\n", orders.get_size());

    // ! DISCUSSION: pop_back has to walk the ENTIRE list to find the
    //   second-to-last node before it can remove the last one.
    //   That's O(n) — one full traversal per call.
    //   A doubly linked list (CT9) solves this with a tail_ pointer: O(1).

    // =========================================================================
    // PART 2 — contains() and remove(): lookup and cancellation
    // =========================================================================

    std::cout << "=== Part 2: Order Lookup & Cancellation ===\n\n";

    // --- 3. Checking order status ---
    std::cout << "--- Looking up orders ---\n";

    // TODO: Use contains() to check if order 2003 is still in the queue.
    //       Print "Order 2003 in queue: true" or "Order 2003 in queue: false".
    //       (Hint: use std::boolalpha or a ternary to produce "true"/"false")

    // TODO: Use contains() to check if order 9999 is in the queue.
    //       Print "Order 9999 in queue: true" or "Order 9999 in queue: false".

    std::cout << "\n";

    // ! DISCUSSION: contains() is read-only — it only traverses, never modifies.
    //   Order 2003 is third in the list — found after inspecting 3 nodes.
    //   Order 9999 doesn't exist — the loop reaches nullptr before finding it.
    //   Both are O(n) worst case. No shortcuts for an unsorted list.

    // --- 4. Processing cancellations ---
    std::cout << "--- Processing cancellations ---\n";

    // ! DISCUSSION: remove() has three cases based on WHERE the match is:
    //   tail match   — trailing pointer reaches the end, unlinks the last node
    //   middle match — trailing pointer stops mid-list, bypasses the node
    //   head match   — no 'previous' node exists; delegates to pop_front()
    //
    // Work through each case in this order so the list state stays clean
    // and every case is visible in the output.

    std::cout << "remove(2004) — tail:   ";
    // TODO: Call remove(2004)
    orders.print();

    std::cout << "remove(2002) — middle: ";
    // TODO: Call remove(2002)
    orders.print();

    std::cout << "remove(2001) — head:   ";
    // TODO: Call remove(2001)
    orders.print();

    std::cout << std::format("Orders remaining: {}\n", orders.get_size());

    return 0;
}
