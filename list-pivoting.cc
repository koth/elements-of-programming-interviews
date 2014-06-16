// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Linked_list_prototype.h"
#include "./Merge_sorted_lists.h"  // uses append_node().

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> list_pivoting(const shared_ptr<ListNode<int>>& L,
                                        int x) {
  auto now = L;
  shared_ptr<ListNode<int>> less_head = nullptr, less_tail = nullptr,
                            equal_head = nullptr, equal_tail = nullptr,
                            larger_head = nullptr, larger_tail = nullptr;
  while (now) {
    if (now->data < x) {
      append_node(now, &less_head, &less_tail);
    } else if (now->data == x) {
      append_node(now, &equal_head, &equal_tail);
    } else {  // now->data > x.
      append_node(now, &larger_head, &larger_tail);
    }
    now = now->next;
  }

  if (less_tail) {
    less_tail->next = nullptr;
  }
  if (equal_tail) {
    equal_tail->next = nullptr;
  }
  if (larger_tail) {
    larger_tail->next = nullptr;
  }
  if (larger_head) {
    append_node(larger_head, &equal_head, &equal_tail);
  }
  if (equal_head) {
    append_node(equal_head, &less_head, &less_tail);
  }
  return less_head;
}
// @exclude

int main(int argc, char** argv) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             4, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                           2, make_shared<ListNode<int>>(
                                  ListNode<int>{5, nullptr})})})})});
  int x = 4;
  auto res = list_pivoting(L, x);
  cout << endl;
  bool before_x = true;
  while (res) {
    if (res->data >= x) {
      before_x = false;
    }
    if (before_x) {
      assert(res->data < x);
    } else {
      assert(res->data >= x);
    }
    cout << res->data << endl;
    res = res->next;
  }
  return 0;
}
