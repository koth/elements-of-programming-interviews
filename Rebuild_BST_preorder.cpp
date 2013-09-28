// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "./BST_prototype.h"

using std::cout;
using std::endl;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

// @include
// Build a BST based on preorder[s : e - 1], return its root.
template <typename T>
BinarySearchTree<T>* rebuild_BST_from_preorder_helper(
    const vector<T> &preorder, int s, int e) {
  if (s < e) {
    int x = s + 1;
    while (x < e && preorder[x] < preorder[s]) {
      ++x;
    }
    return new BinarySearchTree<T>{
        preorder[s],
        unique_ptr<BinarySearchTree<T>>(
            rebuild_BST_from_preorder_helper(preorder, s + 1, x)),
        unique_ptr<BinarySearchTree<T>>(
            rebuild_BST_from_preorder_helper(preorder, x, e))
    };
  }
  return nullptr;
}

// Given a preorder traversal of a BST, return its root.
template <typename T>
BinarySearchTree<T>* rebuild_BST_from_preorder(const vector<T>& preorder) {
  return rebuild_BST_from_preorder_helper(preorder, 0, preorder.size());
}
// @exclude

template <typename T>
void check_ans(const unique_ptr<BinarySearchTree<T>>& n, const T& pre) {
  if (n) {
    check_ans(n->left, pre);
    assert(pre <= n->data);
    cout << n->data << endl;
    check_ans(n->right, n->data);
  }
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4  6
  // should output 1, 2, 3, 4, 5, 6
  // preorder [3, 2, 1, 5, 4, 6]
  vector<int> preorder;
  preorder.emplace_back(3);
  preorder.emplace_back(2);
  preorder.emplace_back(1);
  preorder.emplace_back(5);
  preorder.emplace_back(4);
  preorder.emplace_back(6);
  unique_ptr<BinarySearchTree<int>> root(rebuild_BST_from_preorder(preorder));
  check_ans(root, numeric_limits<int>::min());
  return 0;
}
