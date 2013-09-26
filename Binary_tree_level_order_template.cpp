// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <queue>
#include <memory>

#include "./Binary_tree_prototype_template.h"

using std::cout;
using std::endl;
using std::queue;
using std::unique_ptr;

// @include
template <typename T>
void print_binary_tree_level_order(const unique_ptr<BinaryTree<T>>& n) {
  // Prevent empty tree.
  if (!n) {
    return;
  }

  queue<BinaryTree<T>*> q;
  q.emplace(n.get());
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
    if (--count == 0) {
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
  unique_ptr<BinaryTree<int>> root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  // should output 3
  //               2 5
  //               1 4 6
  print_binary_tree_level_order<int>(root);
  return 0;
}
