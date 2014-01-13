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
    return temp == s1 ? s1 : nullptr;
  }
  return nullptr;  // one list has cycle, and one list has no cycle.
}
// @exclude

int main(int argc, char* argv[]) {
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
