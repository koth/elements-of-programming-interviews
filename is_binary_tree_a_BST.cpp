#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <cassert>
#include <limits>

using namespace std;

// @include
template <typename T>
bool is_BST_helper(const shared_ptr<BinaryTree<T>> &r, const T &lower, 
                   const T &upper) {
  if (!r) {
    return true;
  } else if (r->data < lower || r->data > upper) {
    return false;
  }

  return is_BST_helper(r->left, lower, r->data) &&
         is_BST_helper(r->right, r->data, upper);
}

template <typename T>
bool is_BST(const shared_ptr<BinaryTree<T>> &r) {
  return is_BST_helper(r, numeric_limits<T>::min(), numeric_limits<T>::max());
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
  // should output true
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
