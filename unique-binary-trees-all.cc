// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "./Binary_tree_prototype.h"
#include "./Binary_tree_utils.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

vector<unique_ptr<BinaryTreeNode<int>>>
generate_all_binary_trees_helper(int start, int end);

// @include
vector<unique_ptr<BinaryTreeNode<int>>> generate_all_binary_trees(int n) {
  return generate_all_binary_trees_helper(1, n);
}

vector<unique_ptr<BinaryTreeNode<int>>>
generate_all_binary_trees_helper(int start, int end) {
  vector<unique_ptr<BinaryTreeNode<int>>> res;
  if (start > end) {
    res.emplace_back(nullptr);
    return res;
  }

  for (int i = start; i <= end; ++i) {
    // Try all possible combinations of left subtrees and right subtrees.
    auto left_res = generate_all_binary_trees_helper(start, i - 1),
         right_res = generate_all_binary_trees_helper(i + 1, end);
    for (auto& left : left_res) {
      for (auto& right : right_res) {
        // Use of unique_ptr means that we do not have tree nodes shared
        // across distinct trees.
        res.emplace_back(new BinaryTreeNode<int>{i, move(left), move(right)});
      }
    }
  }
  return res;
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 10);
    n = dis(gen);
  }
  cout << "n = " << n << endl;
  auto res = generate_all_binary_trees(n);
  for (const auto& tree : res) {
    auto sequence = generate_inorder(tree);
    assert(is_sorted(sequence.begin(), sequence.end()));
  }
  return 0;
}
