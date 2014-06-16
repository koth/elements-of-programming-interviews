// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "./Linked_list_prototype.h"
#include "./Reverse_linked_list_iterative.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;
using std::stoi;

// @include
shared_ptr<ListNode<int>> reverse_k(shared_ptr<ListNode<int>> L, int k) {
  bool first_time = true;
  shared_ptr<ListNode<int>> before_pre = nullptr, pre = L,
                            before_post = nullptr, post = L;
  while (pre) {
    int i = k;
    while (i) {
      before_post = post;
      post = post->next;
      --i;
      if (!post) {
        break;
      }
    }
    if (i) {
      return L;
    }

    before_post->next = nullptr;
    reverse_linked_list(pre);
    if (before_pre) {
      before_pre->next = before_post;
    }
    if (first_time) {
      L = before_post;
      first_time = false;
    }
    before_pre = pre, pre->next = post;
    pre = post, before_post = nullptr;
  }
  return L;
}
// @exclude

int main(int argc, char** argv) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                           4, make_shared<ListNode<int>>(
                                  ListNode<int>{5, nullptr})})})})});
  int k;
  if (argc == 2) {
    k = stoi(argv[1]);
  } else {
    k = 2;
  }
  auto res = reverse_k(L, k);
  assert(res->data == 2 && res->next->data == 1 && res->next->next->data == 4 &&
         res->next->next->next->data == 3 &&
         res->next->next->next->next->data == 5 &&
         res->next->next->next->next->next == nullptr);
  while (res) {
    cout << res->data << endl;
    res = res->next;
  }
}
