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
using std::max;
using std::ostream_iterator;
using std::random_device;
using std::stoul;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

int check_ans(vector<int> A) {
  sort(A.begin(), A.end());
  int target = 1;
  for (int a : A) {
    if (a > 0) {
      if (a == target) {
        ++target;
      } else if (a > target) {
        return target;
      }
    }
  }
  return target;
}

// @include
int find_first_missing_positive(vector<int> A) {
  size_t i = 0;
  while (i < A.size()) {
    if (A[i] > 0 && A[i] <= A.size() &&
        A[A[i] - 1] != A[i] && A[i] != i + 1) {
      swap(A[i], A[A[i] - 1]);
    } else {
      ++i;
    }
  }

  for (size_t i = 0; i < A.size(); ++i) {
    if (A[i] != i + 1) {
      return i + 1;
    }
  }
  return A.size() + 1;
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    size_t n;
    if (argc == 2) {
      n = stoul(argv[1]);
    } else {
      uniform_int_distribution<size_t> dis(0, 500000);
      n = dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> dis_n(0, static_cast<int>(n));
    generate_n(back_inserter(A), n, [&] { return dis_n(gen); });
    cout << "n = " << n << endl;
    /*
    copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << find_first_missing_positive(A) << " " << check_ans(A) << endl;
    */
    assert(find_first_missing_positive(A) == check_ans(A));
  }
  return 0;
}
