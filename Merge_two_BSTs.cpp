#include "BST_prototype.h"
#include <iostream>
#include <limits>
#include <cassert>

using namespace std;

// Transform a BST into a circular sorted doubly linked list in-place,
// return the head of the list
template <typename T>
shared_ptr<BinarySearchTree<T> > BST_to_doubly_list(
    const shared_ptr<BinarySearchTree<T> > &n) {
  // Empty subtree
  if (!n) {
    return nullptr;
  }

  // Recursively build the list from left and right subtrees
  auto l_head(BST_to_doubly_list(n->left)), r_head(BST_to_doubly_list(n->right));

  // Append n to the list from left subtree
  shared_ptr<BinarySearchTree<T> > l_tail = nullptr;
  if (l_head) {
    l_tail = l_head->left;
    l_tail->right = n;
    n->left = l_tail;
    l_tail = n;
  } else {
    l_head = l_tail = n;
  }

  // Append the list from right subtree to n
  shared_ptr<BinarySearchTree<T> > r_tail = nullptr;
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

// @include
template <typename T>
void append_node_and_advance(shared_ptr<BinarySearchTree<T> > &head,
                             shared_ptr<BinarySearchTree<T> > &tail,
                             shared_ptr<BinarySearchTree<T> > &n) {
  head ? tail->right = n : head = n;
  tail = n;  // tail to the last node
  n->left = nullptr;  // make n as singly list node
  n = n->right;  // advance n
}

// Merge two sorted linked lists, return the head of list
template <typename T>
shared_ptr<BinarySearchTree<T> > merge_sorted_linked_lists(
    shared_ptr<BinarySearchTree<T> > A, shared_ptr<BinarySearchTree<T> > B) {
  shared_ptr<BinarySearchTree<T> > sorted_list = nullptr, tail = nullptr;

  while (A && B) {
    append_node_and_advance(sorted_list, tail, A->data < B->data ? A : B);
  }

  // Append the remaining of A
  while (A) {
    append_node_and_advance(sorted_list, tail, A);
  }
  // Append the remaining of B
  while (B) {
    append_node_and_advance(sorted_list, tail, B);
  }
  return sorted_list;
}

template <typename T>
shared_ptr<BinarySearchTree<T> > merge_BSTs(
    shared_ptr<BinarySearchTree<T> > A, shared_ptr<BinarySearchTree<T> > B) {
  // Transform BSTs A and B into sorted doubly lists
  A = BST_to_doubly_list(A), B = BST_to_doubly_list(B);
  A->left->right = B->left->right = nullptr;
  return merge_sorted_linked_lists(A, B);
}
// @exclude

template <typename T>
void print_BST_inorder(shared_ptr<BinarySearchTree<T> > n, T pre) {
  if (n) {
    print_BST_inorder(n->left, pre);
    assert(pre <= n->data);
    cout << n->data << ' ';
    print_BST_inorder(n->right, n->data);
  }
}

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinarySearchTree<int> > L = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{3});
  L->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{2});
  L->left->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{1});
  L->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{5});
  L->right->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{4});
  L->right->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{6});
  //     7
  //   2   8
  // 0
  shared_ptr<BinarySearchTree<int> > R = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{7});
  R->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{2});
  R->left->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{0});
  R->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{8});
  shared_ptr<BinarySearchTree<int> > root = merge_BSTs(L, R);
  // should output 0 1 2 2 3 4 5 6 7 8
  print_BST_inorder(root, numeric_limits<int>::min());
  return 0;
}
