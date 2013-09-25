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
// Build a BST based on postorder[s : e - 1], return its root.
template <typename T>
BinarySearchTree<T>* rebuild_BST_postorder_helper(
    const vector<T> &postorder, int s, int e) {
  if (s < e) {
    int x = s;
    while (x < e && postorder[x] < postorder[e - 1]) {
      ++x;
    }
    return new BinarySearchTree<T>{
        postorder[e - 1], 
        unique_ptr<BinarySearchTree<T>>(
          rebuild_BST_postorder_helper(postorder, s, x)),
        unique_ptr<BinarySearchTree<T>>(
          rebuild_BST_postorder_helper(postorder, x, e - 1))
    };
  }
  return nullptr;
}

// Given a postorder traversal of a BST, return its root.
template <typename T>
BinarySearchTree<T>* rebuild_BST_from_postorder(const vector<T>& postorder) {
  return rebuild_BST_postorder_helper(postorder, 0, postorder.size());
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

int main(int argc, char *argv[]) {
  //      1
  //        2
  //          3
  //            4
  //              5
  //                6
  // should output 1, 2, 3, 4, 5, 6
  // postorder [6, 5, 4, 3, 2, 1]
  vector<int> postorder;
  postorder.emplace_back(6);
  postorder.emplace_back(5);
  postorder.emplace_back(4);
  postorder.emplace_back(3);
  postorder.emplace_back(2);
  postorder.emplace_back(1);
  unique_ptr<BinarySearchTree<int>> root(rebuild_BST_from_postorder(postorder));
  check_ans(root, numeric_limits<int>::min());
  return 0;
}
