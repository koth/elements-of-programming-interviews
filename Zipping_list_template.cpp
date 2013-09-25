// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include "./Linked_list_prototype_template.h"
#include "./Reverse_linked_list_iterative_template.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::random_device;
using std::shared_ptr;
using std::uniform_int_distribution;

// @include
template <typename T>
void connect_a_next_to_b_advance_a(shared_ptr<node_t<T>>* a,
                                   const shared_ptr<node_t<T>>& b) {
  shared_ptr<node_t<T>> temp = (*a)->next;
  (*a)->next = b;
  (*a) = temp;
}

template <typename T>
shared_ptr<node_t<T>> zipping_linked_list(const shared_ptr<node_t<T>>& L) {
  shared_ptr<node_t<T>> slow = L, fast = L, pre_slow = nullptr;

  // Find the middle point of L.
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
  shared_ptr<node_t<T>> reverse = reverse_linked_list<T>(slow), curr = L;

  // Zipping the list.
  while (curr && reverse) {
    // Connect curr->next to reverse, and advance curr.
    connect_a_next_to_b_advance_a(&curr, reverse);
    if (curr) {
      // Connect reverse->next to curr, and advance reverse.
      connect_a_next_to_b_advance_a(&reverse, curr);
    }
  }
  return L;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  shared_ptr<node_t<int>> head = nullptr;
  int n;
  if (argc > 2) {
    for (size_t i = 1; i < argc; ++i) {
      auto curr =
          make_shared<node_t<int>>(node_t<int>{atoi(argv[i]), nullptr});
      curr->next = head;
      head = curr;
    }
  } else {
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 1000);
      n = dis(gen);
    }
    for (int i = n; i >= 0; --i) {
      auto curr = make_shared<node_t<int>>(node_t<int>{i, nullptr});
      curr->next = head;
      head = curr;
    }
  }
  shared_ptr<node_t<int>> curr = zipping_linked_list<int>(head);
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
