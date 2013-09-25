// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Linked_list_prototype_template.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
template <typename T>
void deletion_from_list(const shared_ptr<node_t<T>>& v) {
  v->data = v->next->data;
  v->next = v->next->next;
}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<node_t<int>> L;
  L = make_shared<node_t<int>>(node_t<int>{
      1, make_shared<node_t<int>>(node_t<int>{
             2, make_shared<node_t<int>>(node_t<int>{3, nullptr})})});
  deletion_from_list(L);
  assert(L->data == 2 && L->next->data == 3);
  return 0;
}
