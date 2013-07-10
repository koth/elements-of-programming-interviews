// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Binary_tree_prototype_template.h"

#include <cassert>

#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;

// @include
template <typename T>
bool is_symmetric_helper(const shared_ptr<BinaryTree<T>>& l,
                         const shared_ptr<BinaryTree<T>>& r) {
  if (!l && !r) {
    return true;
  } else if (l && r) {
    return l->data == r->data && is_symmetric_helper<T>(l->left, r->right) &&
           is_symmetric_helper<T>(l->right, r->left);
  } else {  // (l && !r) || (!l && r)
    return false;
  }
}

template <typename T>
bool is_symmetric(const shared_ptr<BinaryTree<T>>& n) {
  return (!n || is_symmetric_helper<T>(n->left, n->right));
}
// @exclude

int main(int argc, char *argv[]) {
  // non symmetric tree test
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> non_symm_root =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->left->left =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right->left =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  non_symm_root->right->right =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(is_symmetric<int>(non_symm_root) == false);
  cout << boolalpha << is_symmetric<int>(non_symm_root) << endl;
  // symmetric tree test
  shared_ptr<BinaryTree<int>> symm_root =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  symm_root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  symm_root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(is_symmetric<int>(symm_root) == true);
  cout << boolalpha << is_symmetric<int>(symm_root) << endl;
  // empty tree test
  symm_root = nullptr;
  assert(is_symmetric<int>(symm_root) == true);
  cout << boolalpha << is_symmetric<int>(symm_root) << endl;
  return 0;
}
