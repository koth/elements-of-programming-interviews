// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>

#include "./Binary_tree_with_parent_prototype.h"

using std::cout;
using std::endl;

// @include
template <typename T>
void inorder_traversal(const shared_ptr<BinaryTree<T>> &r) {
  // Empty tree
  if (!r) {
    return;
  }

  shared_ptr<BinaryTree<T>> prev = nullptr, curr = r, next;
  while (curr) {
    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left) {
        next = curr->left;
      } else {
        cout << curr->data << endl;
        next = (curr->right ? curr->right : curr->parent);
      }
    } else if (curr->left == prev) {
      cout << curr->data << endl;
      next = (curr->right ? curr->right : curr->parent);
    } else {  // curr->right == prev
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->parent = root;
  root->left->left = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left;
  root->right = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->parent = root;
  root->right->left = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right;
  root->right->right = 
      shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right;

  // should output 1 2 3 4 5 6
  inorder_traversal<int>(root);
  return 0;
}
