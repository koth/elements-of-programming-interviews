// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
template <typename T>
BinarySearchTree<T>* find_first_equal_k(
    const unique_ptr<BinarySearchTree<T>>& r,
    const T& k) {
  BinarySearchTree<T>* first = nullptr, *curr = r.get();
  while (curr) {
    if (curr->data < k) {
      curr = curr->right.get();
    } else if (curr->data > k) {
      curr = curr->left.get();
    } else {  // curr->data == k.
      // Search for the leftmost in the left subtree.
      first = curr;
      curr = curr->left.get();
    }
  }
  return first;
}
// @exclude

int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 6
  auto root = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  assert(!find_first_equal_k(root, 7));
  assert(find_first_equal_k(root, 6)->data == 6);
  return 0;
}
