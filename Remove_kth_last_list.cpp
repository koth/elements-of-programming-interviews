// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;

// @include
void remove_kth_last(int k, shared_ptr<ListNode<int>>* L) {
  // Advances k steps first.
  shared_ptr<ListNode<int>> ahead = *L;
  int num = k;
  while (ahead && num) {
    ahead = ahead->next;
    --num;
  }

  if (num) {
    throw length_error("not enough nodes in the list");
  }

  shared_ptr<ListNode<int>> pre = nullptr, curr = *L;
  // Finds the k-th last node.
  while (ahead) {
    pre = curr;
    curr = curr->next, ahead = ahead->next;
  }
  if (pre) {
    pre->next = curr->next;
  } else {
    *L = curr->next;  // special case: delete L.
  }
}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
  try {
    remove_kth_last(4, &L);
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }
  remove_kth_last(2, &L);
  assert(L->data == 1 && L->next->data == 3);
  remove_kth_last(2, &L);
  assert(L->data == 3 && L->next == nullptr);
  return 0;
}
