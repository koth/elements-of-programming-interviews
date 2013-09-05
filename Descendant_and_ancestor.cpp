// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
template <typename T>
bool is_r_s_descendant_ancestor_of_m(
    const unique_ptr<BinarySearchTree<T>> &r,
    const unique_ptr<BinarySearchTree<T>> &s,
    const unique_ptr<BinarySearchTree<T>> &m) {
  auto *curr_r = r.get(), *curr_s = s.get();

  // Interleaving searches from r and s.
  while (curr_r && curr_r != s.get() && curr_s && curr_s != r.get()) {
    if (curr_r == m.get() || curr_s == m.get()) {
      return true;
    }
    curr_r = curr_r->data > s->data ?
             curr_r->left.get() : curr_r->right.get();
    curr_s = curr_s->data > r->data ?
             curr_s->left.get() : curr_s->right.get();
  }

  // Keep searching from r.
  while (curr_r && curr_r != s.get()) {
    if (curr_r == m.get()) {
      return true;
    }
    curr_r = curr_r->data > s->data ?
             curr_r->left.get() : curr_r->right.get();
  }
  // Keep searching from s.
  while (curr_s && curr_s != r.get()) {
    if (curr_s == m.get()) {
      return true;
    }
    curr_s = curr_s->data > r->data ?
             curr_s->left.get() : curr_s->right.get();
  }
  return false;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->right->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  root->right->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6});
  assert(
      is_r_s_descendant_ancestor_of_m(root, root->right->right, root->right));
  assert(
      is_r_s_descendant_ancestor_of_m(root->right->right, root, root->right));
  assert(
      !is_r_s_descendant_ancestor_of_m(root, root->right, root->right->right));
  assert(
      !is_r_s_descendant_ancestor_of_m(root->right, root, root->right->right));
  assert(!is_r_s_descendant_ancestor_of_m(
      root->right->left, root->right->right, root->right));
  assert(!is_r_s_descendant_ancestor_of_m(
      root->right->left, root->left->left, root->right));
  return 0;
}
