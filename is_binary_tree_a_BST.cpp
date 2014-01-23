// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::unique_ptr;

bool is_BST_helper(const unique_ptr<BinaryTreeNode<int>>& r,
                   int lower, int upper);

// @include
bool is_BST(const unique_ptr<BinaryTreeNode<int>>& r) {
  return is_BST_helper(r,
                       numeric_limits<int>::min(),
                       numeric_limits<int>::max());
}

bool is_BST_helper(const unique_ptr<BinaryTreeNode<int>>& r,
                   int lower, int upper) {
  if (!r) {
    return true;
  } else if (r->data < lower || r->data > upper) {
    return false;
  }

  return is_BST_helper(r->left, lower, r->data) &&
         is_BST_helper(r->right, r->data, upper);
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
  // should output true.
  assert(is_BST(root) == true);
  cout << boolalpha << is_BST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false.
  assert(!is_BST(root));
  cout << boolalpha << is_BST(root) << endl;
  // should output true.
  assert(is_BST(nullptr) == true);
  cout << boolalpha << is_BST(nullptr) << endl;
  return 0;
}
