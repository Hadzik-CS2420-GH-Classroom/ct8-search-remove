# CT8 — Search & Remove

## Overview

An in-class code-together activity deepening students' understanding of singly linked lists through Farr's Ice Cream's pre-order queue. The simpler operations (destructor, push_front, push_back, pop_front, pop_back, print) are already implemented — students focus on `contains` and `remove`, both of which apply the same trailing pointer pattern seen in `pop_back`.

## Learning Objectives

- Use the **trailing pointer pattern** (`previous`/`current`) to locate and unlink a node by value
- Implement **contains** as a read-only traversal with a single pointer
- Implement **remove** with three distinct cases: empty list, head match, and middle/tail match
- Explain why `contains()` is marked **const** and what the compiler enforces
- Recognize that `contains` and `remove` are both **O(n)** on an unsorted singly linked list

## Files

| File | Focus | TODOs |
|---|---|---|
| `SinglyLinkedList.cpp` | `contains`, `remove` | 6 |
| `main.cpp` | Pre-order queue: last cancellation (Part 1) + lookup and bulk cancellation (Part 2) | 6 |

## Supporting Files

| File | Purpose |
|---|---|
| `Node.h` | Simple `Node` struct (`int data`, `Node* next`) with a two-parameter constructor |
| `SinglyLinkedList.h` | Class declaration with Rule of 5 (all deleted), public interface, `head_`/`size_` members |

## Teaching Order

Start by walking through the given `pop_back` implementation — students don't write it, but reading it establishes the trailing pointer pattern they'll apply in `remove`.

### 1. `SinglyLinkedList.cpp` — contains and remove

1. **contains — Order Lookup** — read-only traversal with single pointer; return true on match, false at nullptr; `const` qualifier enforced by compiler
2. **remove — Head case** — no previous node exists so delegate to `pop_front()`; avoids duplicating temp-pointer logic
3. **remove — Middle/tail case** — trailing pointer setup (same as `pop_back`); stop on data match instead of end; `previous->next = current->next` then delete

### 2. `main.cpp` — Pre-order Queue Scenario

1. **Part 1 — pop_back** — last customer cancels; review the O(n) trailing pointer traversal from the given code
2. **Part 2 — contains** — look up order IDs; demonstrates read-only O(n) search with no shortcut for unsorted data
3. **Part 2 — remove** — cancel orders at tail, middle, then head to show all three cases in sequence

## Key Concepts

- **Trailing pointer pattern**: two pointers where `previous` trails `current` by one step — enables unlinking a node without a backward reference
- **Three-case remove**: empty / head match / middle–tail match — each case requires different handling
- **const correctness**: `contains()` is read-only and marked `const`; the compiler enforces this
- **O(n) vs O(1)**: `pop_back` and `remove` are O(n); `pop_front` and `push_front` are O(1) — a core linked list tradeoff

## Diagrams

PNGs are in `images/`. SVG sources are in `images/svgs/` (for editing).

| Diagram | Referenced In | Shows |
|---|---|---|
| `contains` | `SinglyLinkedList.cpp` | Single pointer walking head→nullptr; highlights match (true) and nullptr (false) |
| `remove` | `SinglyLinkedList.cpp` | Trailing pointer bypass: previous→next redirected to skip the deleted node (middle/tail case) |

## Grading (30 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 2 | Project compiles without errors |
| `pop_back` | 10 | Removes tail correctly, handles single-node and pop to empty |
| `contains` | 9 | Finds head/middle/tail values, returns false for missing and empty list |
| `remove` | 9 | Removes head, middle, tail; no-op for missing value and empty list |

## Comment Conventions

Uses [Better Comments](https://marketplace.visualstudio.com/items?itemName=OmarRwemi.BetterComments) for VS 2022:

| Prefix | Color | Purpose |
|---|---|---|
| `// !` | Important (red) | `DISCUSSION:` teaching notes for instructor walkthrough |
| `// ?` | Question (blue) | `SEE DIAGRAM:` references to visual aids |
| `// TODO:` | Task (orange) | Student exercises (main branch) |
