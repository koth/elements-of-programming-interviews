#include "BST_prototype.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T> > search_first_occurence(
  const shared_ptr<BinarySearchTree<T> > &r, const T &k) {
  if (!r) {
    return nullptr; // no match
  }

  if (r->data < k) {
    return search_first_occurence(r->right, k);
  } else if (r->data > k) {
    return search_first_occurence(r->left, k);
  } else {  // r->data == k
    // Recursively search the left subtree
    shared_ptr<BinarySearchTree<T> > n = search_first_occurence(r->left, k);
    return n ? n : r;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  //    3
  //  2   6
  // 1   4 6
  shared_ptr<BinarySearchTree<int> > root = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{6});
  root->right->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{6});
  assert(!search_first_occurence<int>(root, 7));
  assert(search_first_occurence<int>(root, 6)->data == 6 && search_first_occurence<int>(root, 6)->right->data == 6);
  return 0;
}
