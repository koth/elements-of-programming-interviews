#include "BST_prototype.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T> > find_first_equal_k(
    shared_ptr<BinarySearchTree<T> > r, const T &k) {
  while (r) {
    if (r->data < k) {
      r = r->right;
    } else if (r->data > k) {
      r = r->left;
    } else {  // r->data == k
      // Search for the leftmost in the left subtree
      shared_ptr<BinarySearchTree<T> > l = r->left;
      while (l) {
        if (l->data != k) {
          break;
        } else {
          r = l;
          l = l->left;
        }
      }
      return r;
    }
  }
  return nullptr;  // no match
}
// @exclude

int main(int argc, char *argv[]) {
  //    3
  //  2   5
  // 1   4 6
  shared_ptr<BinarySearchTree<int> > root = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{5});
  root->right->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{6});
  assert(!find_first_equal_k(root, 7));
  assert(find_first_equal_k(root, 6)->data == 6);
  return 0;
}
