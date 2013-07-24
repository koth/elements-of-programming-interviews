// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_H_
#define SOLUTIONS_BST_PROTOTYPE_H_

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
struct BinarySearchTree {
  T data;
  shared_ptr<BinarySearchTree<T>> left, right;
};
// @exclude
#endif  // SOLUTIONS_BST_PROTOTYPE_H_
