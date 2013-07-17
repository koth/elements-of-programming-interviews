// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <random>
#include <stack>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::max;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;
using std::vector;

// O(m^3 n^3) time solution
int check_ans(const vector<deque<bool>> &A) {
  int max = 0;
  for (int a = 0; a < A.size(); ++a) {
    for (int b = 0; b < A[a].size(); ++b) {
      for (int c = a; c < A.size(); ++c) {
        for (int d = b; d < A[c].size(); ++d) {
          bool all_1 = true;
          int count = 0;
          for (int i = a; i <= c; ++i) {
            for (int j = b; j <= d; ++j) {
              if (A[i][j] == false) {
                all_1 = false;
                count = 0;
                break;
              } else {
                ++count;
              }
            }
            if (all_1 == false) {
              break;
            }
          }
          if (all_1 == true && count > max) {
            max = count;
          }
        }
      }
    }
  }
  return max;
}

template <typename T>
T calculate_largest_rectangle(const vector<T> &A) {
  // Calculate L
  stack<int> s;
  vector<int> L;
  for (int i = 0; i < A.size(); ++i) {
    while (!s.empty() && A[s.top()] >= A[i]) {
      s.pop();
    }
    L.emplace_back(s.empty() ? -1 : s.top());
    s.emplace(i);
  }

  // Clear stack for calculating R
  while (!s.empty()) {
    s.pop();
  }
  vector<int> R(A.size());
  for (int i = A.size() - 1; i >= 0; --i) {
    while (!s.empty() && A[s.top()] >= A[i]) {
      s.pop();
    }
    R[i] = s.empty() ? A.size() : s.top();
    s.emplace(i);
  }

  // For each A[i], find its maximum area include it
  T max_area = 0;
  for (int i = 0; i < A.size(); ++i) {
    max_area = max(max_area, A[i] * (R[i] - L[i] - 1));
  }
  return max_area;
}

// @include
int max_rectangle_submatrix(const vector<deque<bool>> &A) {
  vector<vector<int>> table(A.size(), vector<int>(A.front().size()));

  for (int i = A.size() - 1; i >= 0; --i) {
    for (int j = A[i].size() - 1; j >= 0; --j) {
      table[i][j] = A[i][j] ? i + 1 < A.size() ? table[i + 1][j] + 1 : 1 : 0;
    }
  }

  // Find the max among all instances of the largest rectangle
  int max_rect_area = 0;
  for (const vector<int> &t : table) {
    max_rect_area = max(max_rect_area, calculate_largest_rectangle(t));
  }
  return max_rect_area;
}
// @exclude

int main(int argc, char *argv[]) {
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
    //*/
    cout << max_rectangle_submatrix(A) << endl;
    cout << check_ans(A) << endl;
    assert(check_ans(A) == max_rectangle_submatrix(A));
  }
  return 0;
}
