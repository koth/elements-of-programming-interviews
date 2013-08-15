// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_REVERSE_LINKED_LIST_ITERATIVE_TEMPLATE_H_
#define SOLUTIONS_REVERSE_LINKED_LIST_ITERATIVE_TEMPLATE_H_

#include "./Linked_list_prototype_template.h"

// @include
template <typename T>
shared_ptr<node_t<T>> reverse_linked_list(const shared_ptr<node_t<T>> &head) {
  shared_ptr<node_t<T>> prev = nullptr, curr = head;
  while (curr) {
    shared_ptr<node_t<T>> temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}
// @exclude
#endif  // SOLUTIONS_REVERSE_LINKED_LIST_ITERATIVE_TEMPLATE_H_
