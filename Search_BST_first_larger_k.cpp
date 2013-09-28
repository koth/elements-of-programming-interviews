// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
template <typename T>
BinarySearchTree<T>* find_first_larger_k_with_k_exist(
    const unique_ptr<BinarySearchTree<T>>& r,
    const T& k) {
  bool found_k = false;
  BinarySearchTree<T>* curr = r.get(), *first = nullptr;

  while (curr) {
    if (curr->data == k) {
      found_k = true;
      curr = curr->right.get();
    } else if (curr->data > k) {
      first = curr;
      curr = curr->left.get();
    } else {  // curr->data < k.
      curr = curr->right.get();
    }
  }
  return found_k ? first : nullptr;
}
// @exclude

int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 7
  auto root = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{7});
  assert(find_first_larger_k_with_k_exist(root, 1) == root->left.get());
  assert(find_first_larger_k_with_k_exist(root, 5) == root->right->right.get());
  assert(!find_first_larger_k_with_k_exist(root, 6));
  assert(!find_first_larger_k_with_k_exist(root, 7));
  return 0;
}
