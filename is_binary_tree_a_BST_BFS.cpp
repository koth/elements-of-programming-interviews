// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::queue;
using std::unique_ptr;

// @include
struct QNode {
  const unique_ptr<BinaryTreeNode<int>>& node;
  int lower, upper;
};

bool is_BST(const unique_ptr<BinaryTreeNode<int>>& r) {
  queue<QNode> q;
  q.emplace(QNode{r, numeric_limits<int>::min(), numeric_limits<int>::max()});

  while (!q.empty()) {
    if (q.front().node.get()) {
      if (q.front().node->data < q.front().lower ||
          q.front().node->data > q.front().upper) {
        return false;
      }

      q.emplace(QNode{q.front().node->left, q.front().lower,
                      q.front().node->data});
      q.emplace(QNode{q.front().node->right, q.front().node->data,
                      q.front().upper});
    }
    q.pop();
  }
  return true;
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{3});
  root->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{2});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1});
  root->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{5});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{4});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{6});
  // should output true
  assert(is_BST(root) == true);
  cout << boolalpha << is_BST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false
  assert(!is_BST(root));
  cout << boolalpha << is_BST(root) << endl;
  // empty tree, should output true
  assert(is_BST(nullptr) == true);
  cout << boolalpha << is_BST(nullptr) << endl;
  return 0;
}
