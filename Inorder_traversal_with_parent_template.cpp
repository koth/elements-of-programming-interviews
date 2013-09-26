// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <memory>

#include "./Binary_tree_with_parent_prototype.h"

using std::cout;
using std::endl;
using std::unique_ptr;

// @include
template <typename T>
void inorder_traversal(const unique_ptr<BinaryTree<T>>& r) {
  // Empty tree.
  if (!r) {
    return;
  }

  BinaryTree<T>* prev = nullptr, *curr = r.get(), *next;
  while (curr) {
    if (!prev || prev->left.get() == curr || prev->right.get() == curr) {
      if (curr->left) {
        next = curr->left.get();
      } else {
        cout << curr->data << endl;
        next = (curr->right ? curr->right.get() : curr->parent);
      }
    } else if (curr->left.get() == prev) {
      cout << curr->data << endl;
      next = (curr->right ? curr->right.get() : curr->parent);
    } else {  // curr->right.get() == prev.
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTree<int>> root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  // Should output 1 2 3 4 5 6.
  inorder_traversal<int>(root);
  return 0;
}
