// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype_template.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::unique_ptr;

bool is_symmetric_helper(const unique_ptr<BinaryTree<int>>& l,
                         const unique_ptr<BinaryTree<int>>& r);

// @include
bool is_symmetric(const unique_ptr<BinaryTree<int>>& n) {
  return !n || is_symmetric_helper(n->left, n->right);
}

bool is_symmetric_helper(const unique_ptr<BinaryTree<int>>& l,
                         const unique_ptr<BinaryTree<int>>& r) {
  if (!l && !r) {
    return true;
  } else if (l && r) {
    return l->data == r->data && is_symmetric_helper(l->left, r->right) &&
           is_symmetric_helper(l->right, r->left);
  } else {  // (l && !r) || (!l && r)
    return false;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  // non symmetric tree test
  //      3
  //    2   5
  //  1    4 6
  auto non_symm_root = unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(!is_symmetric(non_symm_root));
  cout << boolalpha << is_symmetric(non_symm_root) << endl;
  // symmetric tree test
  unique_ptr<BinaryTree<int>> symm_root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  symm_root->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  symm_root->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(is_symmetric(symm_root) == true);
  cout << boolalpha << is_symmetric(symm_root) << endl;
  // empty tree test
  symm_root = nullptr;
  assert(is_symmetric(symm_root) == true);
  cout << boolalpha << is_symmetric(symm_root) << endl;
  return 0;
}
