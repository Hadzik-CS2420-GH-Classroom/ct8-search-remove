# CT8 -- Implementation Diagrams

Code-block diagrams referenced from `SinglyLinkedList.cpp`.

---

## 1. Remove Head -- Special Case
*`SinglyLinkedList.cpp::remove()` -- target is head, delegate to pop_front()*

![Remove Head](svgs/remove_head.svg)

---

## 2. Remove from Middle -- Trailing Pointer Bypass
*`SinglyLinkedList.cpp::remove()` -- previous->next skips over target, delete target*

![Remove Middle](svgs/remove_middle.svg)
