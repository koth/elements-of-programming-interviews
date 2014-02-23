// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::exception;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int binary_search_unknown_len(const vector<int>& A, int k) {
  // Find the possible range where k exists.
  int p = 0;
  while (true) {
    try {
      int val = A.at((1 << p) - 1);
      if (val == k) {
        return (1 << p) - 1;
      } else if (val > k) {
        break;
      }
    }
    catch (const exception& e) {
      break;
    }
    ++p;
  }

  // Binary search between indices 2^(p - 1) and 2^p - 2.
  int l = 1 << (p - 1), r = (1 << p) - 2;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    try {
      int val = A.at(m);
      if (val == k) {
        return m;
      } else if (val > k) {
        r = m - 1;
      } else {  // A[m] < k
        l = m + 1;
      }
    }
    catch (const exception& e) {
      r = m - 1;  // search the left part if out of boundary.
    }
  }
  return -1;  // nothing matched k.
}
// @exclude

void small_test() {
  vector<int> A = {1, 2, 3};
  assert(binary_search_unknown_len(A, 3) == 2);
  assert(binary_search_unknown_len(A, 1) == 0);
  assert(binary_search_unknown_len(A, 2) == 1);
  assert(binary_search_unknown_len(A, 4) == -1);
}

int main(int argc, char* argv[]) {
  small_test();
  int n, k;
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    if (argc == 2) {
      n = atoi(argv[1]);
      uniform_int_distribution<int> dis(0, 99999);
      k = dis(gen);
    } else if (argc == 3) {
      n = atoi(argv[1]);
      k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 1000000);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(0, (n << 1) - 1);
      k = k_dis(gen);
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> k_dis(0, (n << 1) - 1);
      A.emplace_back(k_dis(gen));
    }
    sort(A.begin(), A.end());
    cout << n << ' ' << k << endl;
    int idx = binary_search_unknown_len(A, k);
    cout << idx << endl;
    assert((idx == -1 && !binary_search(A.cbegin(), A.cend(), k)) ||
           A[idx] == k);
  }
  return 0;
}
