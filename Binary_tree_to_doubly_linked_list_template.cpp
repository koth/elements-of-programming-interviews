#include "Binary_tree_prototype_template.h"
#include <limits>
#include <cassert>
#include <iostream>

using namespace std;

// @include
template <typename T>
shared_ptr<BinaryTree<T>> convert_tree_to_doubly_list(
    const shared_ptr<BinaryTree<T>> &n) {
  if (!n) {
    return nullptr;
  }

  shared_ptr<BinaryTree<T>> L = convert_tree_to_doubly_list(n->left);
  // Join L and n as a doubly linked list
  shared_ptr<BinaryTree<T>> L_tail = nullptr;
  if (L) {
    L_tail = L->left;
    L_tail->right = n, n->left = L_tail;
    L_tail = n;
  } else {
    L = L_tail = n;
  }

  shared_ptr<BinaryTree<T>> R = convert_tree_to_doubly_list(n->right);
  // Join L and R as a doubly linked list
  shared_ptr<BinaryTree<T>> R_tail = nullptr;
  if (R) {
    R_tail = R->left;
    L_tail->right = R, R->left = L_tail;
  } else {
    R_tail = L_tail;
  }
  R_tail->right = L, L->left = R_tail;
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
  // should output 1, 2, 3, 4, 5, 6
  shared_ptr<BinaryTree<int>> head = convert_tree_to_doubly_list(root);
  shared_ptr<BinaryTree<int>> temp = head;
  int pre = numeric_limits<int>::min();
  do {
    assert(pre <= temp->data);
    cout << temp->data << endl;
    temp = temp->right;
  } while (temp != head);
  return 0;
}
