// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <queue>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::queue;
using std::unique_ptr;

// @include
void print_binary_tree_level_order(const unique_ptr<BinaryTreeNode<int>>& r) {
  // Prevents empty tree.
  if (!r) {
    return;
  }

  queue<BinaryTreeNode<int>*> q;
  q.emplace(r.get());
  size_t count = q.size();
  while (!q.empty()) {
    cout << q.front()->data << ' ';
    if (q.front()->left) {
      q.emplace(q.front()->left.get());
    }
    if (q.front()->right) {
      q.emplace(q.front()->right.get());
    }
    q.pop();
    if (--count == 0) {  // Finish printing nodes in the current level.
      cout << endl;
      count = q.size();
    }
  }
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{3, nullptr, nullptr});
  root->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{6, nullptr, nullptr});
  // should output 3
  //               2 5
  //               1 4 6
  print_binary_tree_level_order(root);
  return 0;
}
