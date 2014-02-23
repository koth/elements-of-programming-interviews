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

shared_ptr<BSTNode<int>> BST_to_doubly_list_helper(
    const shared_ptr<BSTNode<int>>& node);

shared_ptr<BSTNode<int>> merge_sorted_linked_lists(
    shared_ptr<BSTNode<int>> A,
    shared_ptr<BSTNode<int>> B);

void append_node_and_advance(shared_ptr<BSTNode<int>>* head,
                             shared_ptr<BSTNode<int>>* tail,
                             shared_ptr<BSTNode<int>>* node);

void append_node(shared_ptr<BSTNode<int>>* head,
                 shared_ptr<BSTNode<int>>* tail,
                 shared_ptr<BSTNode<int>>* node);

// Build a BST from the (s + 1)-th to the e-th node in L.
shared_ptr<BSTNode<int>> build_BST_from_sorted_doubly_list_helper(
    shared_ptr<BSTNode<int>>* L,
    int s,
    int e) {
  shared_ptr<BSTNode<int>> curr = nullptr;
  if (s < e) {
    int m = s + ((e - s) >> 1);
    auto temp = build_BST_from_sorted_doubly_list_helper(L, s, m);
    curr = *L;
    curr->left = temp;
    *L = (*L)->right;
    curr->right = build_BST_from_sorted_doubly_list_helper(L, m + 1, e);
  }
  return curr;
}

shared_ptr<BSTNode<int>> build_BST_from_sorted_doubly_list(
    shared_ptr<BSTNode<int>> L,
    int n) {
  return build_BST_from_sorted_doubly_list_helper(&L, 0, n);
}

shared_ptr<BSTNode<int>> BST_to_doubly_list(
    const shared_ptr<BSTNode<int>>& n) {
  auto res = BST_to_doubly_list_helper(n);
  res->left->right = nullptr;  // breaks the link from tail to head.
  res->left = nullptr;  // breaks the link from head to tail.
  return res;
}

// Transform a BST into a circular sorted doubly linked list in-place,
// return the head of the list.
shared_ptr<BSTNode<int>> BST_to_doubly_list_helper(
    const shared_ptr<BSTNode<int>>& n) {
  // Empty subtree.
  if (!n) {
    return nullptr;
  }

  // Recursively build the list from left and right subtrees.
  auto l_head(BST_to_doubly_list_helper(n->left)),
      r_head(BST_to_doubly_list_helper(n->right));

  // Append n to the list from left subtree.
  shared_ptr<BSTNode<int>> l_tail = nullptr;
  if (l_head) {
    l_tail = l_head->left;
    l_tail->right = n;
    n->left = l_tail;
    l_tail = n;
  } else {
    l_head = l_tail = n;
  }

  // Append the list from right subtree to n.
  shared_ptr<BSTNode<int>> r_tail = nullptr;
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

// Count the list length till end.
int count_len(shared_ptr<BSTNode<int>> L) {
  int len = 0;
  while (L) {
    ++len, L = L->right;
  }
  return len;
}

// @include
shared_ptr<BSTNode<int>> merge_BSTs(
    shared_ptr<BSTNode<int>> A,
    shared_ptr<BSTNode<int>> B) {
  // Transforms BSTs A and B into two sorted doubly linked lists.
  A = BST_to_doubly_list(A), B = BST_to_doubly_list(B);
  int len_A = count_len(A), len_B = count_len(B);
  return build_BST_from_sorted_doubly_list(merge_sorted_linked_lists(A, B),
                                           len_A + len_B);
}

// Merges two sorted doubly linked lists, returns the head of merged list.
shared_ptr<BSTNode<int>> merge_sorted_linked_lists(
    shared_ptr<BSTNode<int>> A,
    shared_ptr<BSTNode<int>> B) {
  shared_ptr<BSTNode<int>> sorted_list = nullptr, tail = nullptr;

  while (A && B) {
    append_node_and_advance(&sorted_list, &tail, A->data < B->data ? &A : &B);
  }

  // Appends the remaining of A.
  if (A) {
    append_node(&sorted_list, &tail, &A);
  }
  // Appends the remaining of B.
  if (B) {
    append_node(&sorted_list, &tail, &B);
  }
  return sorted_list;
}

void append_node_and_advance(shared_ptr<BSTNode<int>>* head,
                             shared_ptr<BSTNode<int>>* tail,
                             shared_ptr<BSTNode<int>>* node) {
  append_node(head, tail, node);
  *node = (*node)->right;  // advances node.
}

void append_node(shared_ptr<BSTNode<int>>* head,
                 shared_ptr<BSTNode<int>>* tail,
                 shared_ptr<BSTNode<int>>* node) {
  if (*head) {
    (*tail)->right = *node, (*node)->left = *tail;
  } else {
    *head = *node;
  }
  *tail = *node;
}
// @exclude

template <typename T>
void print_BST_inorder(shared_ptr<BSTNode<T>> n, const T& pre) {
  if (n) {
    print_BST_inorder(n->left, pre);
    assert(pre <= n->data);
    cout << n->data << ' ';
    print_BST_inorder(n->right, n->data);
  }
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto L = make_shared<BSTNode<int>>(BSTNode<int>{3});
  L->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
  L->left->left = make_shared<BSTNode<int>>(BSTNode<int>{1});
  L->right = make_shared<BSTNode<int>>(BSTNode<int>{5});
  L->right->left =
      make_shared<BSTNode<int>>(BSTNode<int>{4});
  L->right->right =
      make_shared<BSTNode<int>>(BSTNode<int>{6});
  //     7
  //   2   8
  // 0
  auto R = make_shared<BSTNode<int>>(BSTNode<int>{7});
  R->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
  R->left->left = make_shared<BSTNode<int>>(BSTNode<int>{0});
  R->right = make_shared<BSTNode<int>>(BSTNode<int>{8});
  shared_ptr<BSTNode<int>> root = merge_BSTs(L, R);
  // should output 0 1 2 2 3 4 5 6 7 8
  print_BST_inorder(root, numeric_limits<int>::min());
  return 0;
}
