#include <iostream>
#include <array>
#include <cassert>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
class TreeNode {
  public:
    vector<pair<shared_ptr<TreeNode>, double> > edges;
};

// Return (height, diameter) pair
pair<double, double> compute_height_and_diameter(
    const shared_ptr<TreeNode> &r) {
  double diameter = numeric_limits<double>::min();
  array<double, 2> height = {0.0, 0.0};  // store the max 2 heights
  for (const pair<shared_ptr<TreeNode>, double> &e : r->edges) {
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

double compute_diameter(const shared_ptr<TreeNode> &T) {
  return T ? compute_height_and_diameter(T).second : 0.0;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  shared_ptr<TreeNode> r = nullptr;
  assert(0.0 == compute_diameter(r));
  r = shared_ptr<TreeNode>(new TreeNode());
  r->edges.emplace_back(shared_ptr<TreeNode>(new TreeNode()), 10);
  r->edges[0].first->edges.emplace_back(make_pair(shared_ptr<TreeNode>(new TreeNode()), 50));
  r->edges.emplace_back(make_pair(shared_ptr<TreeNode>(new TreeNode()), 20));
  assert(80 == compute_diameter(r));
  cout << compute_diameter(r) << endl;
  r->edges[0].first->edges.emplace_back(make_pair(shared_ptr<TreeNode>(new TreeNode()), 100));
  assert(150 == compute_diameter(r));
  cout << compute_diameter(r) << endl;
  return 0;
}
