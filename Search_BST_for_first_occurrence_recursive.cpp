// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
BSTNode<int>* find_first_equal_k(const unique_ptr<BSTNode<int>>& T, int k) {
  if (!T) {
    return nullptr;  // no match.
  } else if (T->data == k) {
    // Recursively searches the left subtree for first one == k.
    auto* node = find_first_equal_k(T->left, k);
    return node ? node : T.get();
  }
  // Search left or right tree according to T->data and k.
  return find_first_equal_k(T->data < k ? T->right : T->left, k);
}
// @exclude

int main(int argc, char* argv[]) {
  //    3
  //  2   6
  // 1   4 6
  auto root = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left =
      unique_ptr<BSTNode<int>>(new BSTNode<int>{1});
  root->right =
      unique_ptr<BSTNode<int>>(new BSTNode<int>{6});
  root->right->left =
      unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  root->right->right =
      unique_ptr<BSTNode<int>>(new BSTNode<int>{6});
  assert(!find_first_equal_k(root, 7));
  assert(find_first_equal_k(root, 6)->data == 6 &&
         find_first_equal_k(root, 6)->right->data == 6);
  return 0;
}
