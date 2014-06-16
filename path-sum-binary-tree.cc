// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::unique_ptr;

bool has_path_sum_helper(const unique_ptr<BinaryTreeNode<int>>& root,
                         int path_sum, int sum);

// @include
bool has_path_sum(const unique_ptr<BinaryTreeNode<int>>& root, int sum) {
  return has_path_sum_helper(root, 0, sum);
}

bool has_path_sum_helper(const unique_ptr<BinaryTreeNode<int>>& root,
                         int path_sum, int sum) {
  if (root) {
    path_sum += root->data;
    if (!root->left && !root->right) {  // leaf.
      return path_sum == sum;
    }
    // Non-leaf.
    return has_path_sum_helper(root->left, path_sum, sum) ||
           has_path_sum_helper(root->right, path_sum, sum);
  }
  return false;
}
// @exclude

int main(int argc, char** argv) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{3, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{6, nullptr, nullptr});
  assert(has_path_sum(root, 6));
  assert(!has_path_sum(root, 7));
  assert(!has_path_sum(root, 100));
  return 0;
}
