// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

// @include
vector<vector<int>> generate_pascal_triangle(int n) {
  if (n <= 0) {
    return {};
  }

  vector<vector<int>> result;
  result.emplace_back(vector<int>{1});
  for (int i = 1; i < n; ++i) {
    vector<int> curr_row;
    curr_row.emplace_back(1);  // for the first element.
    for (int j = 1; j < i; ++j) {
      curr_row.emplace_back(result.back()[j - 1] + result.back()[j]);
    }
    curr_row.emplace_back(1);  // for the last element.
    result.emplace_back(curr_row);
  }
  return result;
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(0, 10);
    n = dis(gen);
  }
  cout << "n = " << n << endl;
  auto res = generate_pascal_triangle(n);
  for (size_t i = 0; i < res.size(); ++i) {
    for (size_t j = 0; j < res[i].size(); ++j) {
      cout << res[i][j] << ' ';
    }
    cout << endl;
  }
  return 0;
}
