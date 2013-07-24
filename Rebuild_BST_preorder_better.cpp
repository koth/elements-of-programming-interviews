#include "BST_prototype.h"
#include <iostream>
#include <limits>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

// @include
template <typename T>
shared_ptr<BinarySearchTree<T>> rebuild_BST_from_preorder_helper(
    const vector<T> &preorder, int &idx, const T &min, const T &max) { 
  if (idx == preorder.size()) {
    return nullptr;
  }

  T curr = preorder[idx];
  if (curr < min || curr > max) {
    return nullptr;
  }

  ++idx;
  shared_ptr<BinarySearchTree<T> > root(new BinarySearchTree<T>{curr,
      rebuild_BST_from_preorder_helper(preorder, idx, min, curr),
      rebuild_BST_from_preorder_helper(preorder, idx, curr, max)});
  return root;
}

template <typename T>
shared_ptr<BinarySearchTree<T> > rebuild_BST_from_preorder(
    const vector<T> &preorder) {
  int idx = 0;
  return rebuild_BST_from_preorder_helper(preorder, idx, 
                                          numeric_limits<T>::min(),
                                          numeric_limits<T>::max());
}
// @exclude

template <typename T>
void check_ans(const shared_ptr<BinarySearchTree<T>> &n, const T &pre) {
  if (n) {
    check_ans(n->left, pre);
    assert(pre <= n->data);
    cout << n->data << endl;
    check_ans(n->right, n->data);
  }
}

int main(int argc, char *argv[]) {
  //      3
  //    2   5
  //  1    4  6
  // should output 1, 2, 3, 4, 5, 6
  // preorder [3, 2, 1, 5, 4, 6]
  vector<int> preorder;
  preorder.emplace_back(3);
  preorder.emplace_back(2);
  preorder.emplace_back(1);
  preorder.emplace_back(5);
  preorder.emplace_back(4);
  preorder.emplace_back(6);
  shared_ptr<BinarySearchTree<int>> root(rebuild_BST_from_preorder(preorder));
  check_ans<int>(root, numeric_limits<int>::min());
  return 0;
}
