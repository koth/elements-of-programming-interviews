// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "./Binary_tree_prototype_template.h"

using std::cout;
using std::endl;
using std::pair;
using std::unique_ptr;

// @include
template <typename T>
pair<BinaryTree<T>*, int> find_non_k_balanced_node_helper(
    const unique_ptr<BinaryTree<T>>& n,
    int k) {
  // Empty tree.
  if (!n) {
    return {nullptr, 0};
  }

  // Early return if left subtree is not k-balanced.
  auto L = find_non_k_balanced_node_helper<T>(n->left, k);
  if (L.first) {
    return L;
  }
  // Early return if right subtree is not k-balanced.
  auto R = find_non_k_balanced_node_helper<T>(n->right, k);
  if (R.first) {
    return R;
  }

  int node_num = L.second + R.second + 1;  // # of nodes in n.
  if (abs(L.second - R.second) > k) {
    return {n.get(), node_num};
  }
  return {nullptr, node_num};
}

template <typename T>
BinaryTree<T>* find_non_k_balanced_node(const unique_ptr<BinaryTree<T>>& n,
                                        int k) {
  return find_non_k_balanced_node_helper<T>(n, k).first;
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
  int k = 0;
  BinaryTree<int>* ans(find_non_k_balanced_node<int>(root, k));
  assert(ans->data == 2);
  if (ans) {
    cout << ans->data << endl;
  }
  return 0;
}
