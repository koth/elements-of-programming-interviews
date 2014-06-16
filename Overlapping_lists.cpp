// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Checking_cycle.h"
#include "./Linked_list_prototype.h"
#include "./Overlapping_lists_no_cycle.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

int distance_a_b(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b);

// @include
shared_ptr<ListNode<int>> overlapping_lists(shared_ptr<ListNode<int>> L1,
                                            shared_ptr<ListNode<int>> L2) {
  // Store the start of cycle if any.
  shared_ptr<ListNode<int>> s1 = has_cycle(L1), s2 = has_cycle(L2);

  if (!s1 && !s2) {
    return overlapping_no_cycle_lists(L1, L2);
  } else if (s1 && s2) {  // both lists have cycles.
    shared_ptr<ListNode<int>> temp = s2;
    do {
      temp = temp->next;
    } while (temp != s1 && temp != s2);

    // L1 and L2 are not in the same cycle.
    if (temp != s1) {
      return nullptr;
    }

    // Since L1 and L2 are in the same cycle, find the overlapping point
    // if it happens before cycle starts.
    int L1_s1_dis = distance_a_b(L1, s1), L2_s2_dis = distance_a_b(L2, s2);
    if (L1_s1_dis > L2_s2_dis) {
      advance_list_by_k(&L1, L1_s1_dis - L2_s2_dis);
    } else {
      advance_list_by_k(&L2, L2_s2_dis - L1_s1_dis);
    }
    while (L1 != L2 && L1 != s1 && L2 != s2) {
      L1 = L1->next, L2 = L2->next;
    }

    // If L1 == L2 before reaching s1, it means overlapping point happens
    // before cycle starts; otherwise, the point cycle starts is the
    // overlapping point.
    return L1 == L2 ? L1 : s1;
  }
  return nullptr;  // one list has cycle, and one list has no cycle.
}

// Calculates the distance between a and b.
int distance_a_b(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b) {
  int dis = 0;
  while (a != b) {
    a = a->next;
    ++dis;
  }
  return dis;
}
// @exclude

void small_test() {
  shared_ptr<ListNode<int>> L1, L2;
  // L1: 1->2->3->4->5->6-
  //              ^  ^    |
  //              |  |____|
  // L2: 7->8-----
  L1 = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{3, make_shared<ListNode<int>>(ListNode<int>{4, make_shared<ListNode<int>>(ListNode<int>{5, make_shared<ListNode<int>>(ListNode<int>{6, nullptr})})})})})});
  L1->next->next->next->next->next->next = L1->next->next->next->next;

  L2 = make_shared<ListNode<int>>(
      ListNode<int>{7, make_shared<ListNode<int>>(ListNode<int>{8, nullptr})});
  L2->next->next = L1->next->next->next;
  assert(overlapping_lists(L1, L2)->data == 4);

  // L1: 1->2->3->4->5->6-
  //           ^     ^    |
  //           |     |____|
  // L2: 7->8---
  L2->next->next = L1->next->next;
  assert(overlapping_lists(L1, L2)->data == 3);
}

int main(int argc, char* argv[]) {
  small_test();
  shared_ptr<ListNode<int>> L1, L2;
  // L1: 1->2->3->null
  L1 = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
  L2 = L1->next->next;
  assert(overlapping_lists(L1, L2)->data == 3);
  // L2: 4->5->null
  L2 = make_shared<ListNode<int>>(
      ListNode<int>{4, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})});
  assert(!overlapping_lists(L1, L2));
  L1->next->next->next = L1;
  assert(!overlapping_lists(L1, L2));
  L2->next->next = L2;
  assert(!overlapping_lists(L1, L2));
  L2->next->next = L1;
  assert(overlapping_lists(L1, L2));
  return 0;
}
