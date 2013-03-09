#include "Binary_tree_prototype_template.h"
#include "Binary_tree_utils.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

// @include
template <typename T>
shared_ptr<BinaryTree<T>> reconstruct_preorder(
  const vector<shared_ptr<T>> &preorder) {
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
void gen_preorder_with_null(shared_ptr<BinaryTree<T>> n, vector<shared_ptr<T>> &p) {
  if (!n) {
    p.emplace_back(nullptr);
    return;
  }

  p.emplace_back(shared_ptr<T>(new T(n->data)));
  gen_preorder_with_null(n->left, p);
  gen_preorder_with_null(n->right, p);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  // Random test 3000 times
  for (int times = 0; times < 1000; ++times) {
    cout << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
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
