// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <cassert>
#include <memory>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> remove_duplicates(
    const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> pre = nullptr, now = L;
  while (now) {
    if (pre && pre->data == now->data) {
      pre->next = now->next;
      now = now->next;
    } else {
      pre = now;
      now = now->next;
    }
  }
  return L;
}
// @exclude

int main(int argc, char** argv) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      2, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{
                    2, make_shared<ListNode<int>>(ListNode<int>{
                           2, make_shared<ListNode<int>>(ListNode<int>{2, nullptr})})})})});
  shared_ptr<ListNode<int>> pre = nullptr;
  auto res = remove_duplicates(L);
  while (res) {
    if (pre) {
      assert(pre->data != res->data);
    }
    cout << res->data << endl;
    pre = res;
    res = res->next;
  }
  return 0;
}
