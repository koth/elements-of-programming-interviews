// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>

#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;

template <typename T>
struct BinaryTree {
  T data;
  shared_ptr<BinaryTree<T>> left, right, parent;
};

// @include
template <typename T>
shared_ptr<BinaryTree<T>> find_successor(shared_ptr<BinaryTree<T>> n) {
  if (n->right) {
    // Find the leftmost element in n's right subtree
    n = n->right;
    while (n->left) {
      n = n->left;
    }
    return n;
  }

  // Find the first parent whose left child contains n
  while (n->parent && n->parent->right == n) {
    n = n->parent;
  }
  // Return nullptr means n does not have successor
  return n->parent;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4  6
  shared_ptr<BinaryTree<int>>
    root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->parent = nullptr;
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->parent = root;
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->left->left->parent = root->left;
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->parent = root;
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->left->parent = root->right;
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
  root->right->right->parent = root->right;
  // should output 6
  shared_ptr<BinaryTree<int>> node = find_successor(root->right);
  assert(6 == node->data);
  if (node) {
    cout << node->data << endl;
  } else {
    cout << "null" << endl;
  }
  // should output "null"
  node = find_successor(root->right->right);
  assert(!node);
  if (node) {
    cout << node->data << endl;
  } else {
    cout << "null" << endl;
  }
  return 0;
}
