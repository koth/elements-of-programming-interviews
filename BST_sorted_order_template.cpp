#include "BST_prototype.h"
#include <iostream>
#include <stack>

using namespace std;

// @include
template <typename T>
void print_BST_in_sorted_order(const shared_ptr<BinarySearchTree<T>> &n) {
  stack<shared_ptr<BinarySearchTree<T>>> s;
  shared_ptr<BinarySearchTree<T>> curr = n;

  while (!s.empty() || curr) {
    if (curr) {
      s.push(curr);
      curr = curr->left;
    } else {
      curr = s.top();
      s.pop();
      cout << curr->data << endl;
      curr = curr->right;
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinarySearchTree<int>> root = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{3, nullptr});
  root->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{2, nullptr});
  root->left->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{1, nullptr});
  root->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{5, nullptr});
  root->right->left = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{4, nullptr});
  root->right->right = shared_ptr<BinarySearchTree<int>>(new BinarySearchTree<int>{6, nullptr});
  // should output 1 2 3 4 5 6
  print_BST_in_sorted_order<int>(root);
  return 0;
}
