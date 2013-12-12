// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <utility>

using std::array;
using std::cout;
using std::endl;
using std::max;
using std::numeric_limits;
using std::pair;
using std::unique_ptr;
using std::vector;

struct TreeNode;
pair<double, double> compute_height_and_diameter(
    const unique_ptr<TreeNode>& r);

// @include
struct TreeNode {
  vector<pair<unique_ptr<TreeNode>, double>> edges;
};

double compute_diameter(const unique_ptr<TreeNode>& T) {
  return T ? compute_height_and_diameter(T).second : 0.0;
}

// Return (height, diameter) pair.
pair<double, double> compute_height_and_diameter(
    const unique_ptr<TreeNode>& r) {
  double diameter = numeric_limits<double>::min();
  array<double, 2> height = {{0.0, 0.0}};  // store the max two heights.
  for (const auto& e : r->edges) {
    pair<double, double> h_d = compute_height_and_diameter(e.first);
    if (h_d.first + e.second > height[0]) {
      height[1] = height[0];
      height[0] = h_d.first + e.second;
    } else if (h_d.first + e.second > height[1]) {
      height[1] = h_d.first + e.second;
    }
    diameter = max(diameter, h_d.second);
  }
  return {height[0], max(diameter, height[0] + height[1])};
}
// @exclude

int main(int argc, char* argv[]) {
  unique_ptr<TreeNode> r = nullptr;
  assert(0.0 == compute_diameter(r));
  r = unique_ptr<TreeNode>(new TreeNode());
  r->edges.emplace_back(unique_ptr<TreeNode>(new TreeNode()), 10);
  r->edges[0]
      .first->edges.emplace_back(unique_ptr<TreeNode>(new TreeNode()), 50);
  r->edges.emplace_back(unique_ptr<TreeNode>(new TreeNode()), 20);
  assert(80 == compute_diameter(r));
  cout << compute_diameter(r) << endl;
  r->edges[0]
      .first->edges.emplace_back(unique_ptr<TreeNode>(new TreeNode()), 100);
  assert(150 == compute_diameter(r));
  cout << compute_diameter(r) << endl;
  return 0;
}
