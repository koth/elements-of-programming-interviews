#include "Binary_tree_with_parent_prototype.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
int get_depth(shared_ptr<BinaryTree<T>> n) {
  int d = 0;
  while (n) {
    ++d, n = n->parent;
  }
  return d;
}

template <typename T>
shared_ptr<BinaryTree<T>> LCA(shared_ptr<BinaryTree<T>> a, 
                              shared_ptr<BinaryTree<T>> b) {
  int depth_a = get_depth(a), depth_b = get_depth(b);
  if (depth_b > depth_a) {
    swap(a, b);
  }

  // Advance deeper node first
  int depth_diff = depth_a - depth_b;
  while (depth_diff--) {
    a = a->parent;
  }

  // Both pointers advance until they found a common ancestor
  while (a != b) {
    a = a->parent, b = b->parent;
  }
  return a;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->parent = root;
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left;
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->parent = root;
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right;
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right;

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << (LCA(root->left, root->right))->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << (LCA(root->right->left, root->right->right))->data << endl;
  return 0;
}
