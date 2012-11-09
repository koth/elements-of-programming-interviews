#include "Linked_list_prototype_template.h"
#include "BST_prototype.h"
#include <iostream>
#include <limits>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

// @include
// Build a BST from the (s + 1)-th to the e-th node in L
template <typename T>
shared_ptr<BinarySearchTree<T> > build_BST_from_sorted_doubly_list_helper(
    shared_ptr<node_t<T> > &L, const int &s, const int &e) {
  shared_ptr<BinarySearchTree<T> > curr = nullptr;
  if (s < e) {
    int m = s + ((e - s) >> 1);
    curr = shared_ptr<BinarySearchTree<T> >(new BinarySearchTree<T>);
    curr->left = build_BST_from_sorted_doubly_list_helper(L, s, m);
    curr->data = L->data;
    L = L->next;
    curr->right = build_BST_from_sorted_doubly_list_helper(L, m + 1, e);
  }
  return curr;
}

template <typename T>
shared_ptr<BinarySearchTree<T> > build_BST_from_sorted_doubly_list(
  shared_ptr<node_t<T> > L, const int &n) {
  return build_BST_from_sorted_doubly_list_helper(L, 0, n);
}
// @exclude

template <typename T>
void inorder_traversal(shared_ptr<BinarySearchTree<T> > node, const T &pre) {
  if (node) {
    inorder_traversal(node->left, pre);
    assert(pre <= node->data);
    //cout << node->data << ' ';
    inorder_traversal(node->right, node->data);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    shared_ptr<node_t<int> > L = nullptr;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (int i = n; i >= 1; --i) {
      shared_ptr<node_t<int> > temp = shared_ptr<node_t<int> >(new node_t<int>(i));
      temp->next = L;
      L = temp;
    }
    shared_ptr<BinarySearchTree<int> > root = build_BST_from_sorted_doubly_list(L, n);
    inorder_traversal(root, numeric_limits<int>::min());
    //cout << endl;
  }
  return 0;
}
