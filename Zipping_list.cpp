// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "./Linked_list_prototype.h"
#include "./Reverse_linked_list_iterative.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::random_device;
using std::shared_ptr;
using std::stoi;
using std::uniform_int_distribution;

void connect_a_next_to_b_advance_a(const shared_ptr<ListNode<int>>& b,
                                   shared_ptr<ListNode<int>>* a);

// @include
shared_ptr<ListNode<int>> zipping_linked_list(
    const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> slow = L, fast = L, pre_slow = nullptr;

  // Finds the middle point of L.
  while (fast) {
    fast = fast->next;
    if (fast) {
      pre_slow = slow;
      fast = fast->next, slow = slow->next;
    }
  }

  if (!pre_slow) {
    return L;  // only contains one node in the list.
  }
  pre_slow->next = nullptr;  // splits the list into two lists.
  shared_ptr<ListNode<int>> reverse = reverse_linked_list(slow), curr = L;

  // Zips the list.
  while (curr && reverse) {
    // Connects curr->next to reverse, and advances curr.
    connect_a_next_to_b_advance_a(reverse, &curr);
    if (curr) {
      // Connects reverse->next to curr, and advances reverse.
      connect_a_next_to_b_advance_a(curr, &reverse);
    }
  }
  return L;
}

void connect_a_next_to_b_advance_a(const shared_ptr<ListNode<int>>& b,
                                   shared_ptr<ListNode<int>>* a) {
  shared_ptr<ListNode<int>> temp = (*a)->next;
  (*a)->next = b;
  (*a) = temp;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  shared_ptr<ListNode<int>> head = nullptr;
  int n;
  if (argc > 2) {
    for (int i = 1; i < argc; ++i) {
      auto curr =
          make_shared<ListNode<int>>(ListNode<int>{stoi(argv[i]), nullptr});
      curr->next = head;
      head = curr;
    }
  } else {
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 1000);
      n = dis(gen);
    }
    for (int i = n; i >= 0; --i) {
      auto curr = make_shared<ListNode<int>>(ListNode<int>{i, nullptr});
      curr->next = head;
      head = curr;
    }
  }
  shared_ptr<ListNode<int>> curr = zipping_linked_list(head);
  int idx = 0, pre;
  while (curr) {
    if (argc <= 2) {
      if (idx & 1) {
        assert(pre + curr->data == n);
      }
    }
    ++idx;
    cout << curr->data << endl;
    pre = curr->data;
    curr = curr->next;
  }
  return 0;
}
