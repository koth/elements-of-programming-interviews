#include "Binary_tree_with_parent_prototype.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
template <typename T>
shared_ptr<BinaryTree<T>> LCA(shared_ptr<BinaryTree<T>> a, 
                              shared_ptr<BinaryTree<T>> b) {
  unordered_set<shared_ptr<BinaryTree<T>>> hash;
  while (a || b) {
    if (a) {
      if (hash.emplace(a).second == false) {
        return a;  // adds a failed because a exists in hash
      }
      a = a->parent;
    }
    if (b) {
      if (hash.emplace(b).second == false) {
        return b;  // adds b failed because b exists in hash
      }
      b = b->parent;
    }
  }
  // Throw error if a and b are not in the same tree
  throw invalid_argument("a and b are not in the same tree");
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
  cout << (LCA(root->right->left, root->right->right)->data) << endl;
  return 0;
}
