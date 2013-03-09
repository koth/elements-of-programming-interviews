#include "Binary_tree_prototype_template.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <list>
#include <cassert>

using namespace std;

// @include
template <typename T>
void connect_leaves_helper(const shared_ptr<BinaryTree<T>> &n, 
                           list<shared_ptr<BinaryTree<T>>> &L) {
  if (n) {
    if (!n->left && !n->right) {
      L.push_back(n);
    } else {
      connect_leaves_helper(n->left, L);
      connect_leaves_helper(n->right, L);
    }
  }
}

template <typename T>
list<shared_ptr<BinaryTree<T>>> connect_leaves(
    const shared_ptr<BinaryTree<T>> &n) {
  list<shared_ptr<BinaryTree<T>>> L;
  connect_leaves_helper(n, L);
  return L;
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
  // should output 1, 4, 6
  list<shared_ptr<BinaryTree<int>>> L = connect_leaves(root);
  vector<int> output;
  for (auto &l : L) {
    output.push_back(l->data);
    cout << l->data << endl;
  }
  assert(output.size() == 3);
  assert(output[0] == 1 && output[1] == 4 && output[2] == 6);
  return 0;
}
