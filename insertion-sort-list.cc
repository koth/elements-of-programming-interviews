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
shared_ptr<ListNode<int>> insertion_sort(const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> head = nullptr;
  auto now = L;
  while (now) {
    auto next = now->next;
    now->next = nullptr;
    if (head) {
      shared_ptr<ListNode<int>> pre_head_ptr = nullptr, head_ptr = head;
      while (head_ptr && now->data >= head_ptr->data) {
        pre_head_ptr = head_ptr;
        head_ptr = head_ptr->next;
      }
      now->next = head_ptr;
      if (pre_head_ptr) {
        pre_head_ptr->next = now;
      } else {
        head = now;
      }
    } else {
      head = now;
    }
    now = next;
  }
  return head;
}
// @exclude

int main(int argc, char** argv) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             4, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                           2, make_shared<ListNode<int>>(ListNode<int>{5, nullptr})})})})});
  auto res = insertion_sort(L);
  shared_ptr<ListNode<int>> pre = nullptr;
  while (res) {
    assert(!pre || pre->data <= res->data);
    pre = res;
    cout << res->data << endl;
    res = res->next;
  }
  return 0;
}
