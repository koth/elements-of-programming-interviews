#include "BST_prototype.h"
#include <iostream>
#include <cassert>

// @include
template <typename T>
bool is_r_s_descendant_ancestor_of_m(
    const shared_ptr<BinarySearchTree<T>> &r,
    const shared_ptr<BinarySearchTree<T>> &s,
    const shared_ptr<BinarySearchTree<T>> &m) {
  shared_ptr<BinarySearchTree<T>> curr_r = r, curr_s = s;

  // Interleaving searches from r and s
  while (curr_r && curr_r != s && curr_s && curr_s != r) {
    if (curr_r == m || curr_s == m) {
      return true;
    }
    curr_r = curr_r->data > s->data ? curr_r->left : curr_r->right;
    curr_s = curr_s->data > r->data ? curr_s->left : curr_s->right;
  }

  // Keep searching from r
  while (curr_r && curr_r != s) {
    if (curr_r == m) {
      return true;
    }
    curr_r = curr_r->data > s->data ? curr_r->left : curr_r->right;
  }
  // Keep searching from s
  while (curr_s && curr_s != r) {
    if (curr_s == m) {
      return true;
    }
    curr_s = curr_s->data > r->data ? curr_s->left : curr_s->right;
  }
  return false;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  assert(is_r_s_descendant_ancestor_of_m(root, root->right->right, root->right) == true);
  assert(is_r_s_descendant_ancestor_of_m(root->right->right, root, root->right) == true);
  assert(is_r_s_descendant_ancestor_of_m(root, root->right, root->right->right) == false);
  assert(is_r_s_descendant_ancestor_of_m(root->right, root, root->right->right) == false);
  assert(is_r_s_descendant_ancestor_of_m(root->right->left, root->right->right, root->right) == false);
  assert(is_r_s_descendant_ancestor_of_m(root->right->left, root->left->left, root->right) == false);
  return 0;
}
