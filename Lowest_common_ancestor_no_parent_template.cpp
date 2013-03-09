#include "Binary_tree_prototype_template.h"
#include <iostream>
#include <cassert>

using namespace std;

// @include
template <typename T>
shared_ptr<BinaryTree<T>> LCA(const shared_ptr<BinaryTree<T>> &n,
                              const shared_ptr<BinaryTree<T>> &a,
                              const shared_ptr<BinaryTree<T>> &b) {
  if (!n) {  // empty subtree
    return nullptr;
  } else if (n == a || n == b) {
    return n;
  }

  auto l_res = LCA(n->left, a, b), r_res = LCA(n->right, a, b);
  if (l_res && r_res) {
    return n;  // found a and b in different subtrees
  } else {
    return l_res ? l_res : r_res;
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
  shared_ptr<BinaryTree<int>> x = LCA(root, root->left, root->right);
  assert(x->data == 3);
  cout << x->data << endl;
  // should output 5
  x = LCA(root, root->right->left, root->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  // should output 5
  x = LCA(root, root->right, root->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  return 0;
}
