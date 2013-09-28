// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_with_parent_prototype.h"

using std::cout;
using std::endl;
using std::swap;
using std::unique_ptr;

// @include
template <typename T>
int get_depth(const BinaryTree<T>* n) {
  int d = 0;
  while (n) {
    ++d, n = n->parent;
  }
  return d;
}

template <typename T>
BinaryTree<T>* LCA(const unique_ptr<BinaryTree<T>>& a,
                   const unique_ptr<BinaryTree<T>>& b) {
  auto* i = a.get(), *j = b.get();
  int depth_i = get_depth(i), depth_j = get_depth(j);
  if (depth_j > depth_i) {
    swap(i, j);
  }

  // Advance deeper node first.
  int depth_diff = abs(depth_i - depth_j);
  while (depth_diff--) {
    i = i->parent;
  }

  // Both pointers advance until they found a common ancestor.
  while (i != j) {
    i = i->parent, j = j->parent;
  }
  return i;
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{3, nullptr, nullptr, nullptr});
  root->left = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{2, nullptr, nullptr, root.get()});
  root->left->left = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{1, nullptr, nullptr, root->left.get()});
  root->right = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{5, nullptr, nullptr, root.get()});
  root->right->left = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{4, nullptr, nullptr, root->right.get()});
  root->right->right = unique_ptr<BinaryTree<int>>(
      new BinaryTree<int>{6, nullptr, nullptr, root->right.get()});

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << LCA(root->left, root->right)->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << LCA(root->right->left, root->right->right)->data << endl;
  // should output 3
  assert(LCA(root->left, root->right->left)->data == 3);
  cout << LCA(root->left, root->right->left)->data << endl;
  // should output 2
  assert(LCA(root->left, root->left->left)->data == 2);
  cout << LCA(root->left, root->left->left)->data << endl;
  return 0;
}
