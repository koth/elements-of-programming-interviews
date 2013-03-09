#include "BST_prototype.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T>> find_first_larger_k_with_k_exist(
    shared_ptr<BinarySearchTree<T>> r, const T &k) {
  bool found_k = false;
  shared_ptr<BinarySearchTree<T>> first = nullptr;

  while (r) {
    if (r->data == k) {
      found_k = true;
      r = r->right;
    } else if (r->data > k) {
      first = r;
      r = r->left;
    } else {  // r->data < k
      r = r->right;
    }
  }
  return found_k ? first : nullptr;
}
// @exclude

int main(int argc, char *argv[]) {
  //    3
  //  2   5
  // 1   4 7
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{7});
  assert(find_first_larger_k_with_k_exist(root, 1) == root->left);
  assert(find_first_larger_k_with_k_exist(root, 5) == root->right->right);
  assert(!find_first_larger_k_with_k_exist(root, 6));
  assert(!find_first_larger_k_with_k_exist(root, 7));
  return 0;
}
