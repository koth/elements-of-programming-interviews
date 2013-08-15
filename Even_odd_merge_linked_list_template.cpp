// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>

#include "./Linked_list_prototype_template.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;

// @include
template <typename T>
shared_ptr<node_t<T>> even_odd_merge(const shared_ptr<node_t<T>> &L) {
  shared_ptr<node_t<T>> odd = L ? L->next : nullptr;
  shared_ptr<node_t<T>> odd_curr = odd;
  shared_ptr<node_t<T>> pre_even_curr = nullptr, even_curr = L;

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
    pre_even_curr->next = odd;
  }
  return L;
}
// @exclude

int main(int argc, char *argv[]) {
  // input a list in reverse order.
  default_random_engine gen((random_device())());
  shared_ptr<node_t<int>> head = nullptr;
  int n;
  if (argc > 2) {
    for (size_t i = 1; i < argc; ++i) {
      shared_ptr<node_t<int>> curr = shared_ptr<node_t<int>>(new node_t<int>{atoi(argv[i]), nullptr});
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
    for (int i = n - 1; i >= 0; --i) {
      shared_ptr<node_t<int>> curr = shared_ptr<node_t<int>>(new node_t<int>{i, nullptr});
      curr->next = head;
      head = curr;
    }
  }
  shared_ptr<node_t<int>> ans = even_odd_merge(head);
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
