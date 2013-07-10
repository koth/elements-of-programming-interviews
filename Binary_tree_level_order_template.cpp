#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <queue>

using namespace std;

// @include
template <typename T>
void print_binary_tree_level_order(const shared_ptr<BinaryTree<T>> &n) {
  // Prevent empty tree
  if (!n) {
    return;
  }

  queue<shared_ptr<BinaryTree<T>>> q;
  q.emplace(n);
  size_t count = q.size();
  while (!q.empty()) {
    cout << q.front()->data << ' ';
    if (q.front()->left) {
      q.emplace(q.front()->left);
    }
    if (q.front()->right) {
      q.emplace(q.front()->right);
    }
    q.pop();
    if (--count == 0) {
      cout << endl;
      count = q.size();
    }
  }
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
  // should output 3
  //               2 5
  //               1 4 6
  print_binary_tree_level_order<int>(root);
  return 0;
}
