// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_set>

#include "./Binary_tree_with_parent_prototype.h"

using std::cout;
using std::endl;
using std::invalid_argument;
using std::unique_ptr;
using std::unordered_set;

// @include
template <typename T>
BinaryTree<T>* LCA(const unique_ptr<BinaryTree<T>>& a,
                   const unique_ptr<BinaryTree<T>>& b) {
  auto* i = a.get(), *j = b.get();
  unordered_set<const BinaryTree<T>*> hash;
  while (i || j) {
    if (i) {
      if (hash.emplace(i).second == false) {
        return i;  // adds a failed because a exists in hash.
      }
      i = i->parent;
    }
    if (j) {
      if (hash.emplace(j).second == false) {
        return j;  // adds b failed because b exists in hash.
      }
      j = j->parent;
    }
  }
  // Throw error if a and b are not in the same tree.
  throw invalid_argument("a and b are not in the same tree");
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTree<int>> root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << (LCA(root->left, root->right))->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << (LCA(root->right->left, root->right->right)->data) << endl;
  return 0;
}
