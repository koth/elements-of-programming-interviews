// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Binary_tree_prototype_template.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
using std::shared_ptr;

// @include
template <typename T>
struct QNode {
  shared_ptr<BinaryTree<T>> node;
  T lower, upper;
};

template <typename T>
bool is_BST(const shared_ptr<BinaryTree<T>> &n) {
  queue<QNode<T>> q;

  q.emplace(QNode<T>{n, numeric_limits<T>::min(), numeric_limits<T>::max()});
  while (!q.empty()) {
    if (q.front().node) {
      if (q.front().node->data < q.front().lower ||
          q.front().node->data > q.front().upper) {
        return false;
      }

      q.emplace(QNode<T>{q.front().node->left, q.front().lower,
                         q.front().node->data});
      q.emplace(QNode<T>{q.front().node->right, q.front().node->data,
                         q.front().upper});
    }
    q.pop();
  }
  return true;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
  // should output true
  assert(is_BST(root) == true);
  cout << boolalpha << is_BST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false
  assert(is_BST(root) == false);
  cout << boolalpha << is_BST(root) << endl;
  // empty tree, should output true
  assert(is_BST<int>(nullptr) == true);
  cout << boolalpha << is_BST<int>(nullptr) << endl;
  return 0;
}
