// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <memory>
#include <stack>

#include "./BST_prototype.h"

using std::cout;
using std::endl;
using std::stack;
using std::unique_ptr;

// @include
template <typename T>
void print_BST_in_sorted_order(const unique_ptr<BinarySearchTree<T>>& n) {
  stack<const BinarySearchTree<T>*> s;
  const BinarySearchTree<T>* curr = n.get();

  while (!s.empty() || curr) {
    if (curr) {
      s.push(curr);
      curr = curr->left.get();
    } else {
      curr = s.top();
      s.pop();
      cout << curr->data << endl;
      curr = curr->right.get();
    }
  }
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinarySearchTree<int>> root =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3, nullptr});
  root->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2, nullptr});
  root->left->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1, nullptr});
  root->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5, nullptr});
  root->right->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4, nullptr});
  root->right->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6, nullptr});
  // should output 1 2 3 4 5 6
  print_BST_in_sorted_order<int>(root);
  return 0;
}
