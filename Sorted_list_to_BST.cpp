// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Doubly_linked_list_prototype_template.h"

using std::cout;
using std::endl;
using std::make_shared;

// @include
// Build a BST from the (s + 1)-th to the e-th node in L.
// Node numbering is from 1 to n.
template <typename T>
shared_ptr<node_t<T>> build_BST_from_sorted_doubly_list_helper(
    shared_ptr<node_t<T>>* L,
    int s,
    int e) {
  shared_ptr<node_t<T>> curr = nullptr;
  if (s < e) {
    int m = s + ((e - s) >> 1);
    auto temp_left = build_BST_from_sorted_doubly_list_helper(L, s, m);
    curr = *L;  // the last function call sets L to the successor of the
                // maximum node in the tree rooted at temp_left.
    *L = (*L)->next;
    curr->prev = temp_left;
    curr->next = build_BST_from_sorted_doubly_list_helper(L, m + 1, e);
  }
  return curr;
}

template <typename T>
shared_ptr<node_t<T>> build_BST_from_sorted_doubly_list(
    shared_ptr<node_t<T>> L,
    int n) {
  return build_BST_from_sorted_doubly_list_helper(&L, 0, n);
}
// @exclude

int depth = 0;
template <typename T>
void inorder_traversal(const shared_ptr<node_t<T>>& node, const T& pre) {
  if (node) {
    depth++;
    inorder_traversal(node->prev, pre);
    depth--;
    assert(pre <= node->data);
    cout << node->data << ' ' << "; depth = " << depth << endl;
    depth++;
    inorder_traversal(node->next, node->data);
    depth--;
  }
}

int main(int argc, char* argv[]) {
  shared_ptr<node_t<int>> A[1000];

  for (int i = 0; i < 1000; i++) {
    A[i] = make_shared<node_t<int>>(node_t<int>{0});
  }

  shared_ptr<node_t<int>> temp0 = make_shared<node_t<int>>(node_t<int>{0});
  shared_ptr<node_t<int>> temp1 = make_shared<node_t<int>>(node_t<int>{1});
  shared_ptr<node_t<int>> temp2 = make_shared<node_t<int>>(node_t<int>{2});
  shared_ptr<node_t<int>> temp3 = make_shared<node_t<int>>(node_t<int>{3});
  temp0->next = temp1;
  temp1->next = temp2;
  temp2->next = temp3;
  temp3->next = nullptr;
  temp0->prev = nullptr;
  temp1->prev = temp0;
  temp2->prev = temp1;
  temp2->prev = temp2;

  shared_ptr<node_t<int>> L = temp0;
  auto root = build_BST_from_sorted_doubly_list(L, 4);
  inorder_traversal(root, -1);
  return 0;
}
