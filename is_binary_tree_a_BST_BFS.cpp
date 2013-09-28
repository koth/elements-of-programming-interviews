// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>

#include "./Binary_tree_prototype_template.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::queue;
using std::unique_ptr;

// @include
template <typename T>
struct QNode {
  BinaryTree<T>* node;
  T lower, upper;
};

template <typename T>
bool is_BST(const unique_ptr<BinaryTree<T>>& n) {
  queue<QNode<T>> q;
  q.emplace(
      QNode<T>{n.get(), numeric_limits<T>::min(), numeric_limits<T>::max()});

  while (!q.empty()) {
    if (q.front().node) {
      if (q.front().node->data < q.front().lower ||
          q.front().node->data > q.front().upper) {
        return false;
      }

      q.emplace(QNode<T>{q.front().node->left.get(), q.front().lower,
                         q.front().node->data});
      q.emplace(QNode<T>{q.front().node->right.get(), q.front().node->data,
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
  auto root = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
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
  assert(is_BST<int>(nullptr) == true);
  cout << boolalpha << is_BST<int>(nullptr) << endl;
  return 0;
}
