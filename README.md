# CT8 — Search & Remove

## Overview

An in-class code-together activity deepening students' understanding of singly linked lists through Farr's Ice Cream's pre-order queue. The simpler operations (destructor, push_front, push_back, pop_front, print) are already implemented — students focus on the three algorithmically interesting methods: `pop_back` using the trailing pointer pattern, and `contains` / `remove` using search traversal.

## Files

| File | Focus | TODOs |
|---|---|---|
| `SinglyLinkedList.cpp` | `pop_back` (trailing pointer), `contains`, `remove` | ~16 |
| `main.cpp` | Pre-order queue: last cancellation (Part 1) + lookup and bulk cancellation (Part 2) | 7 |

## Supporting Files

| File | Purpose |
|---|---|
| `Node.h` | Simple `Node` struct (`int data`, `Node* next`) with a two-parameter constructor |
| `SinglyLinkedList.h` | Class declaration with Rule of 5 (all deleted), public interface, `head_`/`size_` members |

## Teaching Order

Work through `SinglyLinkedList.cpp` in the order the operations appear in `main.cpp`:

### Part 1 — pop_back

#### 1. `pop_back` -- Last Order Cancelled
- Review the already-implemented methods briefly (destructor, push_front, push_back, pop_front)
- Single-node special case: head IS the tail; just delete and reset
- The **trailing pointer pattern**: `previous` trails one step behind `current`
- Loop condition: stop when `current->next` is nullptr (current is the last node)
- Why one pointer isn't enough: singly-linked nodes have no backward reference
- O(n) cost — must traverse to find the second-to-last node every time
- Preview: doubly linked lists fix this with `prev_` and `tail_` — CT9

### Part 2 — Search and Remove

#### 2. `contains` -- Order Lookup
- Read-only traversal: same pattern as `print()`, but return true on match
- Why `const` matters: the compiler enforces the no-modification promise
- O(n) worst case; no shortcut for an unsorted list

#### 3. `remove` -- Order Cancellation
- Three cases and why each needs different treatment:
  - Empty list: nothing to do
  - Head match: no previous node exists — delegate to `pop_front()`
  - Middle/tail match: trailing pointer is identical to `pop_back`, but stops on a data match
- Pointer surgery: `previous->next = current->next`, then `delete current`
- Show all three cases in sequence (tail → middle → head) using the main.cpp scenario

## Key Concepts

- **Trailing pointer pattern**: two pointers where `previous` trails `current` by one step — enables unlinking a node without a backward reference
- **Three-case remove**: empty / head match / middle–tail match — each case requires different handling
- **const correctness**: `contains()` is read-only and marked `const`; the compiler enforces this
- **O(n) vs O(1)**: `pop_back` and `remove` are O(n); `pop_front` and `push_front` are O(1) — a core linked list tradeoff

## Diagrams

SVG sources are in `images/svgs/`, PNG exports in `images/`.

| Diagram | Referenced In | Shows |
|---|---|---|
| `pop_back` | `SinglyLinkedList.cpp` | Trailing pointer: previous/current traversal, unlink and delete last node |

## Comment Conventions

Uses [Better Comments](https://marketplace.visualstudio.com/items?itemName=OmarRwemi.BetterComments) for VS 2022:

| Prefix | Color | Purpose |
|---|---|---|
| `// !` | Important (red) | `DISCUSSION:` teaching notes for instructor walkthrough |
| `// ?` | Question (blue) | `SEE DIAGRAM:` references to visual aids |
| `// TODO:` | Task (orange) | Student exercises (main branch) |
