// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "./BST_prototype.h"

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

// @include
// Build BST based on subarray A[start : end - 1].
template <typename T>
BinarySearchTree<T>* build_BST_from_sorted_array_helper(const vector<T>& A,
                                                        int start,
                                                        int end) {
  if (start < end) {
    int mid = start + ((end - start) >> 1);
    return new BinarySearchTree<T>{
        A[mid], unique_ptr<BinarySearchTree<T>>(
                    build_BST_from_sorted_array_helper(A, start, mid)),
        unique_ptr<BinarySearchTree<T>>(
            build_BST_from_sorted_array_helper(A, mid + 1, end))};
  }
  return nullptr;
}

template <typename T>
BinarySearchTree<T>* build_BST_from_sorted_array(const vector<T>& A) {
  return build_BST_from_sorted_array_helper(A, 0, A.size());
}
// @exclude

template <typename T>
void traversal_check(const unique_ptr<BinarySearchTree<T>>& root, T* target) {
  if (root) {
    traversal_check(root->left, target);
    assert(*target == root->data);
    ++*target;
    traversal_check(root->right, target);
  }
}

int main(int argc, char* argv[]) {
  for (int times = 0; times < 1000; ++times) {
    vector<int> A;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (size_t i = 0; i < n; ++i) {
      A.emplace_back(i);
    }
    unique_ptr<BinarySearchTree<int>> root =
        unique_ptr<BinarySearchTree<int>>(build_BST_from_sorted_array(A));
    int target = 0;
    traversal_check<int>(root, &target);
  }
  return 0;
}
