#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
pair<shared_ptr<BinaryTree<T>>, int> find_non_k_balanced_node_helper(
    const shared_ptr<BinaryTree<T>> &n, const int &k) {
  // Empty tree
  if (!n) {
    return {nullptr, 0};
  }

  // Early return if left subtree is not k-balanced
  auto L = find_non_k_balanced_node_helper<T>(n->left, k);
  if (L.first) {
    return L;
  }
  // Early return if right subtree is not k-balanced
  auto R = find_non_k_balanced_node_helper<T>(n->right, k);
  if (R.first) {
    return R;
  }

  int node_num = L.second + R.second + 1;  // #nodes in n
  if (abs(L.second - R.second) > k) {
    return {n, node_num};
  }
  return {nullptr, node_num};
}

template <typename T>
shared_ptr<BinaryTree<T>> find_non_k_balanced_node(
    const shared_ptr<BinaryTree<T>> &n, const int &k) {
  return find_non_k_balanced_node_helper<T>(n, k).first;
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  int k = 0;
  shared_ptr<BinaryTree<int>> ans(find_non_k_balanced_node<int>(root, k));
  assert(ans->data == 2);
  if (ans) {
    cout << ans->data << endl;
  }
  return 0;
}
