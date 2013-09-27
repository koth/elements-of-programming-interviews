// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

// @include
int search_smallest(const vector<int>& A) {
  int l = 0, r = A.size() - 1;
  while (l < r) {
    int m = l + ((r - l) >> 1);
    if (A[m] > A[r]) {
      l = m + 1;
    } else {  // A[m] <= A[r].
      r = m;
    }
  }
  return l;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> A;
    unordered_set<int> table;
    for (size_t i = 0; i < n; ++i) {
      while (true) {
        uniform_int_distribution<int> dis(0, 100000);
        int x = dis(gen);
        if (table.emplace(x).second) {
          A.emplace_back(x);
          break;
        }
      }
    }
    sort(A.begin(), A.end());
    uniform_int_distribution<int> n_dis(0, n - 1);
    int shift = n_dis(gen);
    reverse(A.begin(), A.end());
    reverse(A.begin(), A.begin() + shift + 1);
    reverse(A.begin() + shift + 1, A.end());
    /*
       for (size_t i = 0; i < n; ++i) {
       cout << A[i] << ' ';
       }
       cout << endl;
     */
    assert((shift + 1) % n == search_smallest(A));
  }
  // hand-made tests.
  vector<int> A;
  A.emplace_back(2);
  A.emplace_back(3);
  A.emplace_back(4);
  assert(0 == search_smallest(A));
  A.clear();
  A.emplace_back(100);
  A.emplace_back(101);
  A.emplace_back(102);
  A.emplace_back(2);
  A.emplace_back(5);
  assert(3 == search_smallest(A));
  A.clear();
  A.emplace_back(10);
  A.emplace_back(20);
  A.emplace_back(30);
  A.emplace_back(40);
  A.emplace_back(5);
  assert(4 == search_smallest(A));
  return 0;
}
