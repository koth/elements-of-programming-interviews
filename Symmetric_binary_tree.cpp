// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::unique_ptr;

bool is_symmetric_helper(const unique_ptr<BinaryTreeNode<int>>& l_T,
                         const unique_ptr<BinaryTreeNode<int>>& r_T);

// @include
bool is_symmetric(const unique_ptr<BinaryTreeNode<int>>& T) {
  return !T || is_symmetric_helper(T->left, T->right);
}

bool is_symmetric_helper(const unique_ptr<BinaryTreeNode<int>>& l_T,
                         const unique_ptr<BinaryTreeNode<int>>& r_T) {
  if (!l_T && !r_T) {
    return true;
  } else if (l_T && r_T) {
    return l_T->data == r_T->data &&
           is_symmetric_helper(l_T->left, r_T->right) &&
           is_symmetric_helper(l_T->right, r_T->left);
  } else {  // (l_T && !r_T) || (!l_T && r_T)
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
