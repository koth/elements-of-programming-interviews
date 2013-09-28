// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <cassert>
#include <limits>
#include <memory>

#include "./Binary_tree_prototype_template.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::unique_ptr;

// @include
template <typename T>
bool is_BST(const unique_ptr<BinaryTree<T>>& root) {
  auto* n = root.get();
  // Store the value of previous visited node.
  int last = numeric_limits<T>::min();
  bool res = true;

  while (n) {
    if (n->left.get()) {
      // Find the predecessor of n.
      auto* pre = n->left.get();
      while (pre->right.get() && pre->right.get() != n) {
        pre = pre->right.get();
      }

      // Process the successor link.
      if (pre->right.get()) {  // pre->right == n.
        // Revert the successor link if predecessor's successor is n.
        pre->right.release();
        if (last > n->data) {
          res = false;
        }
        last = n->data;
        n = n->right.get();
      } else {  // if predecessor's successor is not n.
        pre->right.reset(n);
        n = n->left.get();
      }
    } else {
      if (last > n->data) {
        res = false;
      }
      last = n->data;
      n = n->right.get();
    }
  }
  return res;
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->left = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->right = unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
  assert(is_BST(root) == true);
  cout << boolalpha << is_BST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false
  assert(!is_BST(root));
  cout << boolalpha << is_BST(root) << endl;
  // should output true
  assert(is_BST<int>(nullptr) == true);
  cout << boolalpha << is_BST<int>(nullptr) << endl;
  return 0;
}
