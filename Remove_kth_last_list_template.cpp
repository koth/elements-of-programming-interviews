// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <stdexcept>
#include <cassert>

#include "./Linked_list_prototype_template.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;

// @include
template <typename T>
void remove_kth_last(shared_ptr<node_t<T>> &L, int k) {
  // Advances k steps first.
  shared_ptr<node_t<T>> ahead = L;
  int num = k;
  while (ahead && num) {
    ahead = ahead->next;
    --num;
  }

  if (num) {
    throw length_error("not enough nodes in the list");
  }

  shared_ptr<node_t<T>> pre = nullptr, curr = L;
  // Finds the k-th last node.
  while (ahead) {
    pre = curr;
    curr = curr->next, ahead = ahead->next;
  }
  if (pre) {
    pre->next = curr->next;
  } else {
    L = curr->next;  // special case: delete L.
  }
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int>> L;
  L = shared_ptr<node_t<int>>(
    new node_t<int>{1, shared_ptr<node_t<int>>(
      new node_t<int>{2, shared_ptr<node_t<int>>(
        new node_t<int>{3, nullptr})})});
  try {
    remove_kth_last(L, 4);
  } catch(const exception &e) {
    cout << e.what() << endl;
  };
  remove_kth_last<int>(L, 2);
  assert(L->data == 1 && L->next->data == 3);
  remove_kth_last<int>(L, 2);
  assert(L->data == 3 && L->next == nullptr);
  return 0;
}
