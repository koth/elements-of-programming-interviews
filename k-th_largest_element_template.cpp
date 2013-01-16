#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

// @include
// Partition A according pivot, return its index after partition
template <typename T>
int partition(vector<T> &A, const int &l, const int &r, const int &pivot) {
  T pivot_value = A[pivot];
  int larger_index = l;

  swap(A[pivot], A[r]);
  for (int i = l; i < r; ++i) {
    if (A[i] > pivot_value) {
      swap(A[i], A[larger_index++]);
    }
  }
  swap(A[r], A[larger_index]);
  return larger_index;
}

template <typename T>
T find_k_th_largest(vector<T> A, const int &k) {
  int l = 0, r = A.size() - 1;

  while (l <= r) {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(l, r);  // generate random int in [l, r]
    int p = partition(A, l, r, dis(gen));
    if (p == k - 1) {
      return A[p];
    } else if (p > k - 1) {
      r = p - 1;
    } else {  // p < k - 1
      l = p + 1;
    }
  }
  // @exclude
  throw length_error("no k-th node in array A");
  // @include
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      k = 1 + rand() % n;
    } else if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      n = 1 + rand() % 100000;
      k = 1 + rand() % n;
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand());
    }
    int res = find_k_th_largest(A, k);
    nth_element(A.begin(), A.begin() + A.size() - k, A.end());
    assert(res == A[A.size() - k]);
  }
  return 0;
}
