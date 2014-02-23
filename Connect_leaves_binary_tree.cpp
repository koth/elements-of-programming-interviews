// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "./Binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::list;
using std::unique_ptr;
using std::vector;

void connect_leaves_helper(const unique_ptr<BinaryTreeNode<int>>& T,
                           list<BinaryTreeNode<int>*>* L);

// @include
list<BinaryTreeNode<int>*> connect_leaves(
    const unique_ptr<BinaryTreeNode<int>>& T) {
  list<BinaryTreeNode<int>*> L;
  connect_leaves_helper(T, &L);
  return L;
}

void connect_leaves_helper(const unique_ptr<BinaryTreeNode<int>>& T,
                           list<BinaryTreeNode<int>*>* L) {
  if (T) {
    if (!T->left && !T->right) {
      L->emplace_back(T.get());
    } else {
      connect_leaves_helper(T->left, L);
      connect_leaves_helper(T->right, L);
    }
  }
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{3, nullptr, nullptr});
  root->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{6, nullptr, nullptr});
  // should output 1, 4, 6
  list<BinaryTreeNode<int>*> L = connect_leaves(root);
  vector<int> output;
  for (const auto& l : L) {
    output.push_back(l->data);
    cout << l->data << endl;
  }
  assert(output.size() == 3);
  assert(output[0] == 1 && output[1] == 4 && output[2] == 6);
  return 0;
}
