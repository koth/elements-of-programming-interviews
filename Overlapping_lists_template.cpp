// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>

#include "./Checking_cycle.h"
#include "./Linked_list_prototype_template.h"
#include "./Overlapping_lists_no_cycle.h"

using std::cout;
using std::endl;

// @include
template <typename T>
shared_ptr<node_t<T>> overlapping_lists(shared_ptr<node_t<T>> L1,
                                        shared_ptr<node_t<T>> L2) {
  // Store the start of cycle if any
  shared_ptr<node_t<T>> s1 = has_cycle<T>(L1), s2 = has_cycle<T>(L2);

  if (!s1 && !s2) {
    return overlapping_no_cycle_lists(L1, L2);
  } else if (s1 && s2) {  // both lists have cycles
    shared_ptr<node_t<T>> temp = s2;
    do {
      temp = temp->next;
    } while (temp != s1 && temp != s2);
    return temp == s1 ? s1 : nullptr;
  }
  return nullptr;  // one list has cycle, one list has no cycle
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int>> L1, L2;
  // L1: 1->2->3->null
  L1 = shared_ptr<node_t<int>>(
    new node_t<int>{1, shared_ptr<node_t<int>>(
      new node_t<int>{2, shared_ptr<node_t<int>>(
        new node_t<int>{3, nullptr})})});
  L2 = L1->next->next;
  assert(overlapping_lists<int>(L1, L2)->data == 3);
  // L2: 4->5->null
  L2 = shared_ptr<node_t<int>>(
    new node_t<int>{4, shared_ptr<node_t<int>>(new node_t<int>{5, nullptr})});
  assert(!overlapping_lists<int>(L1, L2));
  L1->next->next->next = L1;
  assert(!overlapping_lists<int>(L1, L2));
  L2->next->next = L2;
  assert(!overlapping_lists<int>(L1, L2));
  L2->next->next = L1;
  assert(overlapping_lists<int>(L1, L2));
  return 0;
}
