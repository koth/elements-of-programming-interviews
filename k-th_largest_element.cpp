// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::length_error;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

int partition(vector<int>* A, int l, int r, int pivot);

// @include
int find_k_th_largest(vector<int> A, int k) {
  int l = 0, r = A.size() - 1;

  while (l <= r) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(l, r);  // generate random int in [l, r]
    int p = partition(&A, l, r, dis(gen));
    if (p == k - 1) {
      return A[p];
    } else if (p > k - 1) {
      r = p - 1;
    } else {  // p < k - 1.
      l = p + 1;
    }
  }
  // @exclude
  throw length_error("no k-th node in array A");
  // @include
}

// Partition A according pivot, return its index after partition.
int partition(vector<int>* A, int l, int r, int pivot) {
  int pivot_value = (*A)[pivot];
  int larger_index = l;

  swap((*A)[pivot], (*A)[r]);
  for (int i = l; i < r; ++i) {
    if ((*A)[i] > pivot_value) {
      swap((*A)[i], (*A)[larger_index++]);
    }
  }
  swap((*A)[r], (*A)[larger_index]);
  return larger_index;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      uniform_int_distribution<int> k_dis(1, n);
      k = k_dis(gen);
    } else if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 100000);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(1, n - 1);
      k = k_dis(gen);
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, 9999999);
      A.emplace_back(dis(gen));
    }
    int res = find_k_th_largest(A, k);
    nth_element(A.begin(), A.begin() + A.size() - k, A.end());
    assert(res == A[A.size() - k]);
  }
  return 0;
}
