#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <cassert>
#include <limits>

using namespace std;

// @include
template <typename T>
bool is_BST(shared_ptr<BinaryTree<T>> n) {
  // Store the value of previous visited node
  int last = numeric_limits<T>::min();
  bool res = true;

  while (n) {
    if (n->left) {
      // Find the predecessor of n
      shared_ptr<BinaryTree<T>> pre = n->left;
      while (pre->right && pre->right != n) {
        pre = pre->right;
      }

      // Build the successor link
      if (pre->right) {  // pre->right == n
        // Revert the successor link if predecessor's successor is n
        pre->right = nullptr;
        if (last > n->data) {
          res = false;
        }
        last = n->data;
        n = n->right;
      } else {  // if predecessor's successor is not n
        pre->right = n;
        n = n->left;
      }
    } else {
      if (last > n->data) {
        res = false;
      }
      last = n->data;
      n = n->right;
    }
  }
  return res;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
  assert(is_BST(root) == true);
  cout << boolalpha << is_BST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false
  assert(is_BST(root) == false);
  cout << boolalpha << is_BST(root) << endl;
  // should output true
  assert(is_BST<int>(nullptr) == true);
  cout << boolalpha << is_BST<int>(nullptr) << endl;
  return 0;
}
