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

int search_smallest_helper(const vector<int>& A, int l, int r);

// @include
int search_smallest(const vector<int>& A) {
  return search_smallest_helper(A, 0, A.size() - 1);
}

int search_smallest_helper(const vector<int>& A, int l, int r) {
  if (l == r) {
    return l;
  }

  int m = l + ((r - l) >> 1);
  if (A[m] > A[r]) {
    return search_smallest_helper(A, m + 1, r);
  } else if (A[m] < A[r]) {
    return search_smallest_helper(A, l, m);
  } else {  // A[m] == A[r].
    // Smallest element must exist in either left or right side.
    int l_res = search_smallest_helper(A, l, m);
    int r_res = search_smallest_helper(A, m + 1, r);
    return A[r_res] < A[l_res] ? r_res : l_res;
  }
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> A_dis(0, 999999);
    generate_n(back_inserter(A), n, [&] { return A_dis(gen); });
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

  // hand-made tests
  vector<int> A;
  A.emplace_back(2);
  A.emplace_back(2);
  A.emplace_back(2);
  assert(0 == search_smallest(A));
  A.clear();
  A.emplace_back(100);
  A.emplace_back(2);
  A.emplace_back(5);
  A.emplace_back(5);
  assert(1 == search_smallest(A));
  A.clear();
  A.emplace_back(1);
  A.emplace_back(2);
  A.emplace_back(3);
  A.emplace_back(3);
  A.emplace_back(3);
  assert(0 == search_smallest(A));
  A.clear();
  A.emplace_back(5);
  A.emplace_back(2);
  A.emplace_back(3);
  A.emplace_back(3);
  A.emplace_back(3);
  assert(1 == search_smallest(A));
  return 0;
}
