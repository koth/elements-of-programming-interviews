// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "./BST_prototype_shared_ptr.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::shared_ptr;

// @include
// Transform a BST into a circular sorted doubly linked list in-place,
// return the head of the list.
template <typename T>
shared_ptr<BinarySearchTree<T>> BST_to_doubly_list(
    const shared_ptr<BinarySearchTree<T>>& n) {
  // Empty subtree.
  if (!n) {
    return nullptr;
  }

  // Recursively build the list from left and right subtrees.
  auto l_head(BST_to_doubly_list(n->left));
  auto r_head(BST_to_doubly_list(n->right));

  // Append n to the list from left subtree.
  shared_ptr<BinarySearchTree<T>> l_tail = nullptr;
  if (l_head) {
    l_tail = l_head->left;
    l_tail->right = n;
    n->left = l_tail;
    l_tail = n;
  } else {
    l_head = l_tail = n;
  }

  // Append the list from right subtree to n.
  shared_ptr<BinarySearchTree<T>> r_tail = nullptr;
  if (r_head) {
    r_tail = r_head->left;
    l_tail->right = r_head;
    r_head->left = l_tail;
  } else {
    r_tail = l_tail;
  }
  r_tail->right = l_head, l_head->left = r_tail;

  return l_head;
}
// @exclude

int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 6
  auto root = make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{3});
  root->left = make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{2});
  root->left->left =
      make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{1});
  root->right = make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{5});
  root->right->left =
      make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{4});
  root->right->right =
      make_shared<BinarySearchTree<int>>(BinarySearchTree<int>{6});
  shared_ptr<BinarySearchTree<int>> L = BST_to_doubly_list(root);
  shared_ptr<BinarySearchTree<int>> curr = L;
  int pre = numeric_limits<int>::min();
  do {
    assert(pre <= curr->data);
    cout << curr->data << endl;
    pre = curr->data;
    curr = curr->right;
  } while (curr != L);
  return 0;
}
