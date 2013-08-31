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

/*
template <typename T>
int search_smallest_helper(const vector<T> &A, const int &l, const int &r) {
  if (l > r) {
    return -1;
  }

  int m = l + ((r - l) >> 1);
  if (A[m] > A[r]) {
    return search_smallest_helper(A, m + 1, r);
  } else if (A[m] < A[r]) {
    return search_smallest_helper(A, l, m);
  } else {  // A[m] == A[r]
    if (A[l] < A[m]) {
      return l;
    } else if (A[l] > A[m]) {
      return search_smallest_helper(A, l + 1, r);
    } else {  // A[l] == A[m]
      // Smallest may exist in left or right sides
      int l_res = search_smallest_helper(A, l, m - 1);
      int r_res = search_smallest_helper(A, m + 1, r);
      if (r_res == -1) {
        return (l_res == -1 ? m : l_res);
      } else {
        if (l_res == -1) {
          return (A[r_res] < A[m] ? r_res : m);
        } else {
          return (A[r_res] < A[l_res] ? r_res : l_res);
        }
      }
    }
  }
}

template <typename T>
int search_smallest(const vector<T> &A) {
  return search_smallest_helper(A, 0, A.size() - 1);
}
*/

// @include
template <typename T>
int search_smallest_helper(const vector<T> &A, int l, int r) {
  if (l == r) {
    return l;
  }

  int m = l + ((r - l) >> 1);
  if (A[m] > A[r]) {
    return search_smallest_helper(A, m + 1, r);
  } else if (A[m] < A[r]) {
    return search_smallest_helper(A, l, m);
  } else {  // A[m] == A[r]
    // Smallest element must exist in either left or right side.
    int l_res = search_smallest_helper(A, l, m);
    int r_res = search_smallest_helper(A, m + 1, r);
    return A[r_res] < A[l_res] ? r_res : l_res;
  }
}

template <typename T>
int search_smallest(const vector<T> &A) {
  return search_smallest_helper(A, 0, A.size() - 1);
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> A;
    for (size_t i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, 999999);
      A.emplace_back(dis(gen));
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
