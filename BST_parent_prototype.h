// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PARENT_PROTOTYPE_H_
#define SOLUTIONS_BST_PARENT_PROTOTYPE_H_

#include <iostream>
#include <memory>

using std::unique_ptr;

// @include
template <typename T>
struct BinarySearchTree {
  T data;
  unique_ptr<BinarySearchTree<T>> left, right;
  BinarySearchTree<T>* parent;
};
// @exclude
#endif  // SOLUTIONS_BST_PARENT_PROTOTYPE_H_
