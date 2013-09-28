// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "./Largest_rectangle_under_skyline.h"
#include "./Max_submatrix_rectangle_brute_force.h"

using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::max;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int max_rectangle_submatrix(const vector<deque<bool>>& A) {
  vector<vector<int>> table(A.size(), vector<int>(A.front().size()));

  for (int i = A.size() - 1; i >= 0; --i) {
    for (int j = A[i].size() - 1; j >= 0; --j) {
      table[i][j] = A[i][j] ? i + 1 < A.size() ? table[i + 1][j] + 1 : 1 : 0;
    }
  }

  // Find the max among all instances of the largest rectangle.
  int max_rect_area = 0;
  for (const vector<int>& t : table) {
    max_rect_area = max(max_rect_area, calculate_largest_rectangle(t));
  }
  return max_rect_area;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> dis(1, 60);
      n = dis(gen), m = dis(gen);
    }
    vector<deque<bool>> A(n, deque<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        uniform_int_distribution<int> true_or_false(0, 1);
        A[i][j] = true_or_false(gen);
      }
    }
    /*
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << A[i][j] << ' ';
      }
      cout << endl;
    }
    */
    cout << max_rectangle_submatrix(A) << endl;
    cout << max_rectangle_submatrix_brute_force(A) << endl;
    assert(max_rectangle_submatrix_brute_force(A) ==
           max_rectangle_submatrix(A));
  }
  return 0;
}
