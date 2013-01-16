#include "BST_prototype.h"
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
template <typename T>
void find_k_largest_in_BST_helper(const shared_ptr<BinarySearchTree<T> > &r,
                                  const int &k,
  vector<T> &k_elements) {
  // Perform reverse inorder traversal
  if (r && k_elements.size() < k) {
    find_k_largest_in_BST_helper(r->right, k, k_elements);
    if (k_elements.size() < k) {
      k_elements.emplace_back(r->data);
      find_k_largest_in_BST_helper(r->left, k, k_elements);
    }
  }
}

template <typename T>
vector<T> find_k_largest_in_BST(const shared_ptr<BinarySearchTree<T> > &root,
                                const int &k) {
  vector<T> k_elements;
  find_k_largest_in_BST_helper(root, k, k_elements);
  return k_elements;
}
// @exclude

int main(int argc, char *argv[]) {
  //    3
  //  2   5
  // 1   4 6
  shared_ptr<BinarySearchTree<int> > root = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{3});
  root->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{2});
  root->left->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{1});
  root->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{5});
  root->right->left = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{4});
  root->right->right = shared_ptr<BinarySearchTree<int> >(new BinarySearchTree<int>{6});
  srand(time(nullptr));
  int k;
  if (argc == 2) {
    k = atoi(argv[1]);
  } else {
    k = 1 + rand() % 6;
  }
  vector<int> ans = find_k_largest_in_BST(root, k);
  for (int i = 1; i < ans.size(); ++i) {
    assert(ans[i - 1] >= ans[i]);
  }
  return 0;
}
