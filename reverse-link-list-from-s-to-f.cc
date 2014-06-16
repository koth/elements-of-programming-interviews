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
shared_ptr<ListNode<int>> reverse_sublist_s_f(
    shared_ptr<ListNode<int>> L, int s, int f) {
  if (s == f) {  // no need to reverse since s == f.
    return L;
  }

  // Finds (s - 1)-th and s-th nodes.
  size_t count = 1;
  shared_ptr<ListNode<int>> prev_s_ptr = nullptr, s_ptr = L;
  while (count < s) {
    ++count;
    prev_s_ptr = s_ptr;
    s_ptr = s_ptr->next;
  }

  // Breaks the links to form a list starting from s_ptr to f_ptr.
  if (prev_s_ptr) {
    prev_s_ptr->next = nullptr;
  }
  // Reverses the sublist from s-th node to f-th node.
  shared_ptr<ListNode<int>> prev = nullptr, curr = s_ptr, f_ptr, next_f_ptr;
  while (count < f) {
    ++count;
    f_ptr = curr->next;
    next_f_ptr = f_ptr->next;
    curr->next = prev;
    prev = curr;
    curr = f_ptr;
  }
  f_ptr->next = prev;
  s_ptr->next = next_f_ptr;

  if (prev_s_ptr) {
    prev_s_ptr->next = f_ptr;
    return L;
  } else {
    return f_ptr;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
  auto res = reverse_sublist_s_f(L, 3, 3);
  assert(res->data == 1 && res->next->data == 2 && res->next->next->data == 3 && !res->next->next->next);
  while (res) {
    cout << res->data << endl;
    res = res->next;
  }

  res = reverse_sublist_s_f(L, 2, 3);
  assert(res->data == 1 && res->next->data == 3 && res->next->next->data == 2 && !res->next->next->next);
  while (res) {
    cout << res->data << endl;
    res = res->next;
  }

  L = make_shared<ListNode<int>>(ListNode<int>{
      3, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})});
  res = reverse_sublist_s_f(L, 1, 2);
  assert(res->data == 5 && res->next->data == 3 && !res->next->next);
  while (res) {
    cout << res->data << endl;
    res = res->next;
  }
  return 0;
}
