// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
template <typename T>
bool search_m_before_t(BinarySearchTree<T>* p,
                       const unique_ptr<BinarySearchTree<T>>& t,
                       const unique_ptr<BinarySearchTree<T>>& m) {
  while (p && p != t.get() && p != m.get()) {
    p = p->data > t->data ? p->left.get() : p->right.get();
  }
  return p == m.get();
}

template <typename T>
bool is_r_s_descendant_ancestor_of_m(
    const unique_ptr<BinarySearchTree<T>>& r,
    const unique_ptr<BinarySearchTree<T>>& s,
    const unique_ptr<BinarySearchTree<T>>& m) {
  auto* cur_r = r.get(), *cur_s = s.get();

  // Interleaving searches from r and s.
  while (cur_r && cur_r != s.get() && cur_s && cur_s != r.get()) {
    if (cur_r == m.get() || cur_s == m.get()) {
      return true;
    }
    cur_r = cur_r->data > s->data ? cur_r->left.get() : cur_r->right.get();
    cur_s = cur_s->data > r->data ? cur_s->left.get() : cur_s->right.get();
  }

  // Reach the other before reaching m.
  if (cur_r == s.get() || cur_s == r.get()) {
    return false;
  }
  // Try to search m before reaching the other.
  return search_m_before_t(cur_r, s, m) || search_m_before_t(cur_s, r, m);
}
// @exclude

void small_test() {
  auto root = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
  root->left = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4});
  assert(!is_r_s_descendant_ancestor_of_m(root, root->left, root->left->right));
}

int main(int argc, char* argv[]) {
  small_test();
  return 0;
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3});
  root->left = unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2});
  root->left->left =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1});
  root->right =
      unique_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5});
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
