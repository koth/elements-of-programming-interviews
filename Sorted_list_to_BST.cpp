#include "Doubly_linked_list_prototype_template.h"
#include <iostream>
#include <limits>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

// @include
// Build a BST from the (s + 1)-th to the e-th node in L.
// Node numbering is from 1 to n.
template <typename T>
shared_ptr<node_t<T>> build_BST_from_sorted_doubly_list_helper(
    shared_ptr<node_t<T>> &L, const int &s, const int &e) {
  shared_ptr<node_t<T>> curr = nullptr;
  if (s < e) {
    int m = s + ((e - s) >> 1);
    auto temp_left = build_BST_from_sorted_doubly_list_helper(L, s, m);
    curr = L; // the last function call sets L to the successor of the
              // maximum node in the tree rooted at temp_left
    L = L->next;
    curr->prev = temp_left;
    curr->next = build_BST_from_sorted_doubly_list_helper(L, m + 1, e);
  }
  return curr;
}

template <typename T>
shared_ptr<node_t<T>> build_BST_from_sorted_doubly_list(
    shared_ptr<node_t<T>> L, const int &n) {
  return build_BST_from_sorted_doubly_list_helper(L, 0, n);
}
// @exclude

int depth = 0;
template <typename T>
void inorder_traversal(shared_ptr<node_t<T>> node, const T &pre) {
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

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  /*
  for (int times = 0; times < 1000; ++times) {
    shared_ptr<node_t<int>> L = nullptr;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (int i = n; i >= 1; --i) {
      shared_ptr<node_t<int>> temp = shared_ptr<node_t<int>>(new node_t<int>{i});
      temp->next = L;
      L = temp;
    }
    auto root = build_BST_from_sorted_doubly_list(L, n);
    inorder_traversal(root, numeric_limits<int>::min());
    //cout << endl;
  }
  */

  shared_ptr<node_t<int>> A[1000];
  
  for ( int i = 0 ; i < 1000; i++ ) {
    A[i] = shared_ptr<node_t<int>>(new node_t<int>{0});

  shared_ptr<node_t<int>> temp0 = shared_ptr<node_t<int>>(new node_t<int>{0});
  shared_ptr<node_t<int>> temp1 = shared_ptr<node_t<int>>(new node_t<int>{1});
  shared_ptr<node_t<int>> temp2 = shared_ptr<node_t<int>>(new node_t<int>{2});
  shared_ptr<node_t<int>> temp3 = shared_ptr<node_t<int>>(new node_t<int>{3});
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
  inorder_traversal(root, -1 );


  return 0;
}
