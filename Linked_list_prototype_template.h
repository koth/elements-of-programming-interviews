// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_LINKED_LIST_PROTOTYPE_TEMPLATE_H_
#define SOLUTIONS_LINKED_LIST_PROTOTYPE_TEMPLATE_H_

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
struct node_t {
  T data;
  shared_ptr<node_t<T>> next;
};
// @exclude
#endif  // SOLUTIONS_LINKED_LIST_PROTOTYPE_TEMPLATE_H_
