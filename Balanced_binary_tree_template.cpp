#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
int get_height(const shared_ptr<BinaryTree<T>> &n) {
  if (!n) {
    return -1;  // base case
  }

  int l_height = get_height(n->left);
  if (l_height == -2) {
    return -2;  // left subtree is not balanced
  }
  int r_height = get_height(n->right);
  if (r_height == -2) {
    return -2;  // right subtree is not balanced
  }

  if (abs(l_height - r_height) > 1) {
    return -2;  // current node n is not balanced
  }
  return max(l_height, r_height) + 1;  // return the height
}

template <typename T>
bool is_balanced_binary_tree(const shared_ptr<BinaryTree<T>> &n) {
  return get_height(n) != -2;
}
// @exclude

int main(int argc, char *argv[]) {
  //  balanced binary tree test
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(is_balanced_binary_tree<int>(root) == true);
  cout << boolalpha << is_balanced_binary_tree<int>(root) << endl;
  // non-balanced binary tree test
  root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  assert(is_balanced_binary_tree<int>(root) == false);
  cout << boolalpha << is_balanced_binary_tree<int>(root) << endl;
  return 0;
}
