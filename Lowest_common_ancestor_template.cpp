// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

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
int get_depth(const unique_ptr<BinaryTree<T>>& n) {
  auto* temp = n.get();
  int d = 0;
  while (temp) {
    ++d, temp = temp->parent;
  }
  return d;
}

template <typename T>
BinaryTree<T>* LCA(const unique_ptr<BinaryTree<T>>& a,
                   const unique_ptr<BinaryTree<T>>& b) {
  int depth_a = get_depth(a), depth_b = get_depth(b);
  auto *i = a.get(), *j = b.get();
  if (depth_b > depth_a) {
    swap(i, j);
  }

  // Advance deeper node first.
  int depth_diff = depth_a - depth_b;
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

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << (LCA(root->left, root->right))->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << (LCA(root->right->left, root->right->right))->data << endl;
  return 0;
}
