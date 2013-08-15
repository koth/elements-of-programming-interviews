// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_CHECKING_CYCLE_H_
#define SOLUTIONS_CHECKING_CYCLE_H_

#include "./Linked_list_prototype_template.h"

// @include
template <typename T>
shared_ptr<node_t<T>> has_cycle(const shared_ptr<node_t<T>> &head) {
  shared_ptr<node_t<T>> fast = head, slow = head;

  while (slow && slow->next && fast && fast->next && fast->next->next) {
    slow = slow->next, fast = fast->next->next;
    if (slow == fast) {  // there is a cycle.
      // Calculates the cycle length.
      int cycle_len = 0;
      do {
        ++cycle_len;
        fast = fast->next;
      } while (slow != fast);

      // Tries to find the start of the cycle.
      slow = head, fast = head;
      // Fast pointer advances cycle_len first.
      while (cycle_len--) {
        fast = fast->next;
      }
      // Both pointers advance at the same time.
      while (slow != fast) {
        slow = slow->next, fast = fast->next;
      }
      return slow;  // the start of cycle.
    }
  }
  return nullptr;  // no cycle.
}
// @exclude
#endif  // SOLUTIONS_SWAP_BITS_H_
