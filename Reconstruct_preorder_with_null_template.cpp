// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

#include "./Binary_tree_prototype_template.h"
#include "./Binary_tree_utils.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
shared_ptr<BinaryTree<T>> reconstruct_preorder(
  const vector<shared_ptr<T>>& preorder) {
  stack<shared_ptr<BinaryTree<T>>> s;
  for (auto it = preorder.crbegin(); it != preorder.crend(); ++it) {
    if (!(*it)) {
      s.emplace(nullptr);
    } else {  // non-nullptr
      shared_ptr<BinaryTree<T>> l = s.top();
      s.pop();
      shared_ptr<BinaryTree<T>> r = s.top();
      s.pop();
      s.emplace(new BinaryTree<T>{*(*it), l, r});
    }
  }
  return s.top();
}
// @exclude

template <typename T>
void gen_preorder_with_null(shared_ptr<BinaryTree<T>> n,
                            vector<shared_ptr<T>>& p) {
  if (!n) {
    p.emplace_back(nullptr);
    return;
  }

  p.emplace_back(shared_ptr<T>(new T(n->data)));
  gen_preorder_with_null(n->left, p);
  gen_preorder_with_null(n->right, p);
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  // Random test 3000 times
  for (int times = 0; times < 1000; ++times) {
    cout << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    shared_ptr<BinaryTree<int>> root = generate_rand_binary_tree<int>(n);
    vector<shared_ptr<int>> p;
    gen_preorder_with_null(root, p);
    shared_ptr<BinaryTree<int>> x = reconstruct_preorder<int>(p);
    assert(is_two_binary_trees_equal(root, x));
    delete_binary_tree(root);
    delete_binary_tree(x);
  }
  return 0;
}
