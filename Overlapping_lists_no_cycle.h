// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_
#define SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_

#include "./Linked_list_prototype.h"

int count_len(shared_ptr<ListNode<int>> L);
void advance_list_by_k(shared_ptr<ListNode<int>>* L, int k);

// @include
shared_ptr<ListNode<int>> overlapping_no_cycle_lists(
    shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
  // Counts the lengths of L1 and L2.
  int L1_len = count_len(L1), L2_len = count_len(L2);

  // Advances the longer list.
  advance_list_by_k(L1_len > L2_len ? &L1 : &L2, abs(L1_len - L2_len));

  while (L1 && L2 && L1 != L2) {
    L1 = L1->next, L2 = L2->next;
  }
  return L1;  // nullptr means no overlap between L1 and L2.
}

// Counts the list length till end.
int count_len(shared_ptr<ListNode<int>> L) {
  int len = 0;
  while (L) {
    ++len, L = L->next;
  }
  return len;
}

void advance_list_by_k(shared_ptr<ListNode<int>>* L, int k) {
  while (k--) {
    *L = (*L)->next;
  }
}
// @exclude
#endif  // SOLUTIONS_OVERLAPPING_LISTS_NO_CYCLE_H_
