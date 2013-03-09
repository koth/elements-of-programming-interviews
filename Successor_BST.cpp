#include "BST_parent_prototype.h"
#include <iostream>
#include <cassert>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T>> find_successor_BST(
  shared_ptr<BinarySearchTree<T>> n) {
  if (n->right) {
    // Find the smallest element in n's right subtree
    n = n->right;
    while (n->left) {
      n = n->left;
    }
    return n;
  }

  // Find the first parent which is larger than n
  while (n->parent && n->parent->right == n) {
    n = n->parent;
  }
  // Return nullptr means n is the largest in this BST
  return n->parent;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4  6
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->parent = nullptr;
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->parent = root;
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->left->left->parent = root->left;
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->parent = root;
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->left->parent = root->right;
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  root->right->right->parent = root->right;
  // should output 6
  shared_ptr<BinarySearchTree<int>> node = find_successor_BST(root->right);
  assert(6 == node->data);
  if (node) {
    cout << node->data << endl;
  } else {
    cout << "null" << endl;
  }
  // should output "null"
  node = find_successor_BST(root->right->right);
  assert(!node);
  if (node) {
    cout << node->data << endl;
  } else {
    cout << "null" << endl;
  }
  return 0;
}
