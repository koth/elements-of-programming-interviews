#include "BST_prototype.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T>> find_first_equal_k(
    const shared_ptr<BinarySearchTree<T>> &r, const T &k) {
  if (!r) {
    return nullptr;  // no match
  } else if (r->data == k) {
    // Recursively search the left subtree for first one == k
    shared_ptr<BinarySearchTree<T>> n = find_first_equal_k(r->left, k);
    return n ? n : r;
  }
  // Search left or right tree according to r->data and k
  return find_first_equal_k(r->data < k ? r->right : r->left, k);
}
// @exclude

int main(int argc, char *argv[]) {
  //    3
  //  2   6
  // 1   4 6
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  assert(!find_first_equal_k<int>(root, 7));
  assert(find_first_equal_k<int>(root, 6)->data == 6 && find_first_equal_k<int>(root, 6)->right->data == 6);
  return 0;
}
