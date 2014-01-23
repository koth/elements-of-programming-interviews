// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::unique_ptr;

bool is_symmetric_helper(const unique_ptr<BinaryTreeNode<int>>& l_n,
                         const unique_ptr<BinaryTreeNode<int>>& r_n);

// @include
bool is_symmetric(const unique_ptr<BinaryTreeNode<int>>& n) {
  return !n || is_symmetric_helper(n->left, n->right);
}

bool is_symmetric_helper(const unique_ptr<BinaryTreeNode<int>>& l_n,
                         const unique_ptr<BinaryTreeNode<int>>& r_n) {
  if (!l_n && !r_n) {
    return true;
  } else if (l_n && r_n) {
    return l_n->data == r_n->data &&
           is_symmetric_helper(l_n->left, r_n->right) &&
           is_symmetric_helper(l_n->right, r_n->left);
  } else {  // (l_n && !r_n) || (!l_n && r_n)
    return false;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  // non symmetric tree test
  //      3
  //    2   5
  //  1    4 6
  auto non_symm_root = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  non_symm_root->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  non_symm_root->left->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  non_symm_root->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  non_symm_root->right->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  non_symm_root->right->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  assert(!is_symmetric(non_symm_root));
  cout << boolalpha << is_symmetric(non_symm_root) << endl;
  // symmetric tree test
  unique_ptr<BinaryTreeNode<int>> symm_root =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  symm_root->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  symm_root->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>());
  assert(is_symmetric(symm_root) == true);
  cout << boolalpha << is_symmetric(symm_root) << endl;
  // empty tree test
  symm_root = nullptr;
  assert(is_symmetric(symm_root) == true);
  cout << boolalpha << is_symmetric(symm_root) << endl;
  return 0;
}
