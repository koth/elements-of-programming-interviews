#include "Binary_tree_prototype_template.h"
#include <iostream>

using namespace std;

// @include
template <typename T>
void inorder_traversal(shared_ptr<BinaryTree<T>> n) {
  while (n) {
    if (n->left) {
      // Find the predecessor of n
      shared_ptr<BinaryTree<T>> pre = n->left;
      while (pre->right && pre->right != n) {
        pre = pre->right;
      }

      // Build the successor link
      if (pre->right) {  // pre->right == n
        // Revert the successor link if predecessor's successor is n
        pre->right = nullptr;
        cout << n->data << endl;
        n = n->right;
      } else {  // if predecessor's successor is not n
        pre->right = n;
        n = n->left;
      }
    } else {
      cout << n->data << endl;
      n = n->right;
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{3});
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{2});
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{1});
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{5});
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{4});
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>{6});
  // should output 1 2 3 4 5 6
  inorder_traversal<int>(root);
  return 0;
}
