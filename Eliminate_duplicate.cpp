// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
void eliminate_duplicate(vector<T> *A) {
  sort(A->begin(), A->end());  // makes identical elements become neighbors.
  // unique() removes adjacent duplicates and returns an iterator to the
  // element the follows the last element not removed. The effect of resize()
  // is to restrict A to the distinct element.
  A->resize(distance(A->begin(), unique(A->begin(), A->end())));
}
// @exclude

template <typename T>
void check_ans(const vector<T> &A) {
  for (int i = 1; i < A.size(); ++i) {
    assert(A[i] != A[i - 1]);
  }
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<int> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(0, 100000);
      n = dis(gen);
    }
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, n - 1);
      A.emplace_back(dis(gen));
    }
    eliminate_duplicate(&A);
    check_ans(A);
  }
  return 0;
}
