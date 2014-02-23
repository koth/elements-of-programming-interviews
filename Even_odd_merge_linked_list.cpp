// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include "./Linked_list_prototype.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::random_device;
using std::shared_ptr;
using std::uniform_int_distribution;

// @include
shared_ptr<ListNode<int>> even_odd_merge(const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> odd_first = L ? L->next : nullptr;
  shared_ptr<ListNode<int>> odd_curr = odd_first;
  shared_ptr<ListNode<int>> pre_even_curr = nullptr, even_curr = L;

  while (even_curr && odd_curr) {
    even_curr->next = odd_curr->next;
    pre_even_curr = even_curr;
    even_curr = even_curr->next;
    if (even_curr) {
      odd_curr->next = even_curr->next;
      odd_curr = odd_curr->next;
    }
  }

  // Odd number of nodes.
  if (even_curr) {
    pre_even_curr = even_curr;
  }
  // Prevents empty list.
  if (pre_even_curr) {
    pre_even_curr->next = odd_first;
  }
  return L;
}
// @exclude

int main(int argc, char* argv[]) {
  // input a list in reverse order.
  default_random_engine gen((random_device())());
  shared_ptr<ListNode<int>> head = nullptr;
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 1000);
    n = dis(gen);
  }
  for (int i = n - 1; i >= 0; --i) {
    auto curr = make_shared<ListNode<int>>(ListNode<int>{i, nullptr});
    curr->next = head;
    head = curr;
  }
  shared_ptr<ListNode<int>> ans = even_odd_merge(head);
  int x = 0;
  while (ans) {
    if (argc <= 2) {
      assert(x == ans->data);
      x += 2;
      if (x >= n) {
        x = 1;
      }
    }
    cout << ans->data << endl;
    ans = ans->next;
  }
  return 0;
}
