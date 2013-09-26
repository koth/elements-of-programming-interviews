// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "./Binary_tree_prototype_template.h"

using std::cout;
using std::endl;
using std::list;
using std::unique_ptr;
using std::vector;

// @include
template <typename T>
void connect_leaves_helper(const unique_ptr<BinaryTree<T>>& n,
                           list<BinaryTree<T>*>* L) {
  if (n) {
    if (!n->left && !n->right) {
      L->emplace_back(n.get());
    } else {
      connect_leaves_helper(n->left, L);
      connect_leaves_helper(n->right, L);
    }
  }
}

template <typename T>
list<BinaryTree<T>*> connect_leaves(const unique_ptr<BinaryTree<T>>& n) {
  list<BinaryTree<T>*> L;
  connect_leaves_helper(n, &L);
  return L;
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTree<int>> root =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{3, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{2, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{1, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{5, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{4, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTree<int>>(new BinaryTree<int>{6, nullptr, nullptr});
  // should output 1, 4, 6
  list<BinaryTree<int>*> L = connect_leaves(root);
  vector<int> output;
  for (const auto& l : L) {
    output.push_back(l->data);
    cout << l->data << endl;
  }
  assert(output.size() == 3);
  assert(output[0] == 1 && output[1] == 4 && output[2] == 6);
  return 0;
}
