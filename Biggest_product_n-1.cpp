#include <iostream>
#include <numeric>
#include <cassert>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
template <typename T>
T find_biggest_n_1_product(const vector<T> &A) {
  // Build forward product L, and backward product R
  vector<T> L, R(A.size());
  partial_sum(A.cbegin(), A.cend(), back_inserter(L), multiplies<T>());
  partial_sum(A.crbegin(), A.crend(), R.rbegin(), multiplies<T>());

  // Find the biggest product of (n - 1) numbers
  T max_product = numeric_limits<T>::min();
  for (int i = 0; i < A.size(); ++i) {
    T forward = i > 0 ? L[i - 1] : 1;
    T backward = i + 1 < A.size() ? R[i + 1] : 1;
    max_product = max(max_product, forward * backward);
  }
  return max_product;
}
// @exclude

// n^2 checking
template <typename T>
T check_ans(const vector<T> &A) {
  T max_product = numeric_limits<T>::min();
  for (int i = 0; i < A.size(); ++i) {
    T product = 1;
    for (int j = 0; j < i; ++j) {
      product *= A[j];
    }
    for (int j = i + 1; j < A.size(); ++j) {
      product *= A[j];
    }
    if (product > max_product) {
      max_product = product;
    }
  }
  return max_product;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    vector<int> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 2 + rand() % 10;
    }
    for (size_t i = 0; i < n; ++i) {
      A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % 10);
      cout << A[i] << ' ';
    }
    cout << endl;
    int res = find_biggest_n_1_product(A);
    assert(res == check_ans(A));
    cout << res << endl;
  }
  return 0;
}
