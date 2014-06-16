// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

void combinations_helper(int n, int k,  int start, vector<int>* ans,
                         vector<vector<int>>* res);

// @include
vector<vector<int>> combinations(int n, int k) {
  vector<vector<int>> res;
  vector<int> ans;
  combinations_helper(n, k, 0, &ans, &res);
  return res;
}

void combinations_helper(int n, int k,  int start, vector<int>* ans,
                         vector<vector<int>>* res) {
  if (ans->size() == k) {
    res->emplace_back(*ans);
    return;
  }

  if (k - ans->size() <= n - (start + 1)) {
    combinations_helper(n, k, start + 1, ans, res);
  }
  ans->emplace_back(start + 1);
  combinations_helper(n, k, start + 1, ans, res);
  ans->pop_back();
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  int n, k;
  if (argc == 3) {
    n = stoi(argv[1]), k = stoi(argv[2]);
  } else {
    uniform_int_distribution<int> n_dis(1, 10);
    n = n_dis(gen);
    uniform_int_distribution<int> k_dis(0, n);
    k = k_dis(gen);
  }
  auto res = combinations(n, k);
  cout << "n = " << n << ", k = " << k << endl;
  for (const auto& vec : res) {
    for (int a : vec) {
      cout << a << " ";
    }
    cout << endl;
  }
  return 0;
}
