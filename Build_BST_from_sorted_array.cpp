#include "BST_prototype.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

// @include
// Build BST based on subarray A[start : end - 1]
template <typename T>
shared_ptr<BinarySearchTree<T>> build_BST_from_sorted_array_helper(
    const vector<T> &A, const int &start, const int &end) {
  if (start < end) {
    int mid = start + ((end - start) >> 1);
    return shared_ptr<BinarySearchTree<T>>(new BinarySearchTree<T>{
        A[mid],
        build_BST_from_sorted_array_helper(A, start, mid),
        build_BST_from_sorted_array_helper(A, mid + 1, end)}
    );
  }
  return nullptr;
}

template <typename T>
shared_ptr<BinarySearchTree<T>> build_BST_from_sorted_array(
    const vector<T> &A) {
  return build_BST_from_sorted_array_helper(A, 0, A.size());
}
// @exclude

template <typename T>
void traversal_check(shared_ptr<BinarySearchTree<T>> root, T &target) {
  if (root) {
    traversal_check(root->left, target);
    assert(target == root->data);
    ++target;
    traversal_check(root->right, target);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    vector<int> A;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (size_t i = 0; i < n; ++i) {
      A.push_back(i);
    }
    shared_ptr<BinarySearchTree<int>> root = build_BST_from_sorted_array(A);
    int target = 0;
    traversal_check<int>(root, target);
  }
  return 0;
}
