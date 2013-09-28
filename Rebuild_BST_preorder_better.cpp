// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "./BST_prototype.h"

using std::cout;
using std::endl;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

// @include
template <typename T>
BinarySearchTree<T>* rebuild_BST_from_preorder_helper(
    const vector<T>& preorder, int* idx, const T& min, const T& max) {
  if (*idx == preorder.size()) {
    return nullptr;
  }

  T curr = preorder[*idx];
  if (curr < min || curr > max) {
    return nullptr;
  }

  ++*idx;
  return new BinarySearchTree<T>{
      curr, unique_ptr<BinarySearchTree<T>>(
                rebuild_BST_from_preorder_helper(preorder, idx, min, curr)),
      unique_ptr<BinarySearchTree<T>>(
          rebuild_BST_from_preorder_helper(preorder, idx, curr, max))};
}

template <typename T>
BinarySearchTree<T>* rebuild_BST_from_preorder(const vector<T>& preorder) {
  int idx = 0;
  return rebuild_BST_from_preorder_helper(
      preorder, &idx, numeric_limits<T>::min(), numeric_limits<T>::max());
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
  check_ans<int>(root, numeric_limits<int>::min());
  return 0;
}
