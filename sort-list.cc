// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include "./Linked_list_prototype.h"
#include "./Merge_sorted_lists.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;

// @include
shared_ptr<ListNode<int>> sort_list(shared_ptr<ListNode<int>> L) {
  // Base case. L has 0 or 1 node.
  if (L == nullptr || L->next == nullptr) {
    return L;
  }

  // Finds the middle point of L.
  shared_ptr<ListNode<int>> slow = L, fast = L, pre_slow = nullptr;
  while (fast) {
    fast = fast->next;
    if (fast) {
      pre_slow = slow;
      fast = fast->next, slow = slow->next;
    }
  }

  pre_slow->next = nullptr;  // splits the list into two lists.
  fast = sort_list(L), slow = sort_list(slow);
  return merge_sorted_linked_lists(fast, slow);
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    shared_ptr<ListNode<int>> L = nullptr;
    int n;
    uniform_int_distribution<int> dis(0, 99);
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      n = dis(gen);
    }
    for (int i = n; i > 0; --i) {
      shared_ptr<ListNode<int>> temp =
          make_shared<ListNode<int>>(ListNode<int>{dis(gen), nullptr});
      temp->next = L;
      L = temp;
    }

    auto sorted_head = sort_list(L);
    int count = 0;
    int pre = numeric_limits<int>::min();
    while (sorted_head) {
      assert(pre <= sorted_head->data);
      pre = sorted_head->data;
      sorted_head = sorted_head->next;
      ++count;
    }
    assert(count == n);
  }
  return 0;
}
