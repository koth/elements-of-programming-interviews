// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>

#include "./Linked_list_prototype_template.h"

using std::cout;
using std::endl;

// @include
template <typename T>
void deletion_from_list(const shared_ptr<node_t<T>> &v) {
  v->data = v->next->data;
  v->next = v->next->next;
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int>> L;
  L = shared_ptr<node_t<int>>(
    new node_t<int>{1, shared_ptr<node_t<int>>(
      new node_t<int>{2, shared_ptr<node_t<int>>(
        new node_t<int>{3, nullptr})})});
  deletion_from_list(L);
  assert(L->data == 2 && L->next->data == 3);
  return 0;
}
