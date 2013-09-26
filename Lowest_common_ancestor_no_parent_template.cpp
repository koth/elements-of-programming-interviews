// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Binary_tree_prototype_template.h"

using std::cout;
using std::endl;
using std::unique_ptr;

// @include
template <typename T>
BinaryTree<T>* LCA(const unique_ptr<BinaryTree<T>>& n,
                   const unique_ptr<BinaryTree<T>>& a,
                   const unique_ptr<BinaryTree<T>>& b) {
  if (!n) {  // empty subtree.
    return nullptr;
  } else if (n == a || n == b) {
    return n.get();
  }

  auto* l_res = LCA(n->left, a, b), *r_res = LCA(n->right, a, b);
  if (l_res && r_res) {
    return n.get();  // found a and b in different subtrees.
  } else {
    return l_res ? l_res : r_res;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTree<int>> root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  // should output 3
  auto* x = LCA(root, root->left, root->right);
  assert(x->data == 3);
  cout << x->data << endl;
  // should output 5
  x = LCA(root, root->right->left, root->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  // should output 5
  x = LCA(root, root->right, root->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  return 0;
}
