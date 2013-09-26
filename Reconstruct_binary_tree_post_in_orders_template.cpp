// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "./Binary_tree_prototype_template.h"
#include "./Binary_tree_utils.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

// @include
template <typename T>
BinaryTree<T>* reconstruct_post_in_orders_helper(
    const vector<T>& post, int post_s, int post_e,
    const vector<T>& in, int in_s, int in_e) {
  if (post_e > post_s && in_e > in_s) {
    auto it = find(in.cbegin() + in_s, in.cbegin() + in_e, post[post_e - 1]);
    auto left_tree_size = distance(in.cbegin(), it) - in_s;

    return new BinaryTree<T>{post[post_e - 1],
      // Recursively build the left subtree.
      unique_ptr<BinaryTree<T>>(reconstruct_post_in_orders_helper<T>(
          post, post_s, post_s + left_tree_size,
          in, in_s, distance(in.cbegin(), it))),
      // Recursively build the right subtree.
      unique_ptr<BinaryTree<T>>(reconstruct_post_in_orders_helper<T>(
          post, post_s + left_tree_size, post_e - 1,
          in, distance(in.cbegin(), it) + 1, in_e))
      };
  }
  return nullptr;
}

template <typename T>
BinaryTree<T>* reconstruct_post_in_orders(const vector<T>& post,
                                          const vector<T>& in) {
  return reconstruct_post_in_orders_helper(post, 0, post.size(),
                                           in, 0, in.size());
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    cout << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    unique_ptr<BinaryTree<int>> root = generate_rand_binary_tree<int>(n, true);
    vector<int> post = generate_postorder(root);
    vector<int> in = generate_inorder(root);
    auto res =
        unique_ptr<BinaryTree<int>>(reconstruct_post_in_orders<int>(post, in));
    assert(is_two_binary_trees_equal<int>(root, res));
    delete_binary_tree(&root);
    delete_binary_tree(&res);
  }
  return 0;
}
