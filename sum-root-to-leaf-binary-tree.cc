// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::equal;
using std::unique_ptr;

int preorder_traversal(const unique_ptr<BinaryTreeNode<int>>& root, int num);

// @include
int sum_root_to_leaf(const unique_ptr<BinaryTreeNode<int>>& root) {
  return preorder_traversal(root, 0);
}

int preorder_traversal(const unique_ptr<BinaryTreeNode<int>>& root, int num) {
  if (!root) {
    return 0;
  }

  num = (num << 1) + root->data;
  if (!root->left && !root->right) {  // leaf.
    return num;
  }
  // non-leaf.
  return preorder_traversal(root->left, num) +
         preorder_traversal(root->right, num);
}
// @exclude

int main(int argc, char** argv) {
  //      1
  //    1   0
  //  0    1 0
  unique_ptr<BinaryTreeNode<int>> root =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{0, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{0, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{0, nullptr, nullptr});
  auto res = sum_root_to_leaf(root);
  assert(res == 15);
  return 0;
}
