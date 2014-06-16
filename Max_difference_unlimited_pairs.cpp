// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int max_profit_unlimited_pairs(const vector<int>& A) {
  int profit = 0;
  for (int i = 1; i < A.size(); ++i) {
    int delta = A[i] - A[i - 1];
    if (delta > 0) {
      profit += delta;
    }
  }
  return profit;
}
// @exclude

int check_ans(const vector<int> &A) {
  int profit = 0;

  for (int i = 1; i < A.size(); ++i) {
    if (A[i] > A[i - 1]) {
      profit += A[i] - A[i - 1];
    }
  }
  return profit;
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  int n = 5;
  // random tests for n = 40, k = 4 for 100 times
  for (int times = 0; times < 100; ++times) {
    vector<int> A;
    uniform_int_distribution<int> dis(0, 99);
    for (int i = 0; i < n; ++i) {
      A.emplace_back(dis(gen));
    }
    cout << "n = " << n << endl;
    cout << check_ans(A) << endl;
    cout << max_profit_unlimited_pairs(A) << endl;
    assert(check_ans(A) == max_profit_unlimited_pairs(A));
  }

  // For input
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 10000);
    n = dis(gen);
  }
  vector<int> A;
  uniform_int_distribution<int> dis(0, 99);
  for (int i = 0; i < n; ++i) {
    A.emplace_back(dis(gen));
  }
  cout << "n = " << n << endl;
  cout << max_profit_unlimited_pairs(A) << endl;
  return 0;
}
