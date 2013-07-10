#include "BST_prototype.h"
#include <cassert>
#include <iostream>

using namespace std;

// @include
template <typename T>
bool search_min_first_BST(const shared_ptr<BinarySearchTree<T>> &r,
                          const T &k) {
  if (!r || r->data > k) {
    return false;
  } else if (r->data == k) {
    return true;
  }

  // Search the right subtree if the smallest key in the right subtree is
  // greater than or equal to k.
  if (r->right && k >= r->right->data) {
    return search_min_first_BST(r->right, k);
  }
  return search_min_first_BST(r->left, k);
}
// @exclude

int main(int argc, char *argv[]) {
  // A min-first BST
  //    1
  //  2   4
  // 3   5 7
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{7});
  assert(search_min_first_BST(root, 1) == true);
  assert(search_min_first_BST(root, 3) == true);
  assert(search_min_first_BST(root, 5) == true);
  assert(search_min_first_BST(root, 6) == false);
  return 0;
}
