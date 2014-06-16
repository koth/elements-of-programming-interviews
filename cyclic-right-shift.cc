// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> cyclically_right_shift_list(
    shared_ptr<ListNode<int>> L, int k) {
  if (!L) {
    return L;
  }

  // Computes n, the length of L, and stores the tails of the list.
  auto tail = L;
  int n = 1;
  while (tail->next) {
    ++n, tail = tail->next;
  }
  // We only need to rotate right k % n nodes.
  k %= n;

  // No need to rotate if k == 0.
  if (!k) {
    return L;
  }

  tail->next = L;  // makes a cycle by connecting the tail to the head.
  // Advances (n - k) steps.
  int step = n - k;
  shared_ptr<ListNode<int>> prev = nullptr, curr = L;
  while (step--) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = nullptr;  // prev is the new tail.
  return curr;
}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
  auto res = cyclically_right_shift_list(L, 2);
  assert(res->data == 2 && res->next->data == 3 && res->next->next->data == 1 && !res->next->next->next);
  while (res) {
    cout << res->data << endl;
    res = res->next;
  }
  return 0;
}
