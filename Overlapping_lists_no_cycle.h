// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_
#define SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_

#include "./Linked_list_prototype_template.h"

// @include
// Counts the list length till end.
template <typename T>
int count_len(shared_ptr<node_t<T>> L) {
  int len = 0;
  while (L) {
    ++len, L = L->next;
  }
  return len;
}

template <typename T>
void advance_list_by_k(shared_ptr<node_t<T>>* L, int k) {
  while (k--) {
    *L = (*L)->next;
  }
}

template <typename T>
shared_ptr<node_t<T>> overlapping_no_cycle_lists(shared_ptr<node_t<T>> L1,
                                                 shared_ptr<node_t<T>> L2) {
  // Count the lengths of L1 and L2
  int L1_len = count_len(L1), L2_len = count_len(L2);

  // Advance the longer list
  advance_list_by_k(L1_len > L2_len ? &L1 : &L2, abs(L1_len - L2_len));

  while (L1 && L2 && L1 != L2) {
    L1 = L1->next, L2 = L2->next;
  }
  return L1;  // nullptr means no overlap between L1 and L2
}
// @exclude
#endif  // SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_
