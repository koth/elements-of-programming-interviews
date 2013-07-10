// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./BST_prototype.h"
#include <cassert>
#include <iostream>

// @include
template <typename T>
shared_ptr<BinarySearchTree<T>> find_LCA(
    shared_ptr<BinarySearchTree<T>> x,
    const shared_ptr<BinarySearchTree<T>>& s,
    const shared_ptr<BinarySearchTree<T>>& b) {
  while (x->data < s->data || x->data > b->data) {
    while (x->data < s->data) {
      x = x->right;  // LCA must be in x's right child
    }
    while (x->data > b->data) {
      x = x->left;  // LCA must be in x's left child
    }
  }

  // x->data >= s->data && x->data <= b->data
  return x;  // x is LCA
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinarySearchTree<int>> root =
    shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left =
    shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left =
    shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right =
    shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  assert(3 == find_LCA(root, root->left->left, root->right->left)->data);
  assert(5 == find_LCA(root, root->right->left, root->right->right)->data);
  assert(2 == find_LCA(root, root->left->left, root->left)->data);
  return 0;
}
