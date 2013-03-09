#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

// @include
template <typename T>
bool has_2_sum(const vector<T> &A, const T &t) {
  int j = 0, k = A.size() - 1;

  while (j <= k) {
    if (A[j] + A[k] == t) {
      return true;
    } else if (A[j] + A[k] < t) {
      ++j;
    } else {  // A[j] + A[k] > t
      --k;
    }
  }
  return false;
}

template <typename T>
bool has_3_sum(vector<T> A, const T &t) {
  sort(A.begin(), A.end());

  for (const T &a : A) {
    // Find if the sum of two numbers in A equals to t - a
    if (has_2_sum(A, t - a)) {
      return true;
    }
  }
  return false;
}
// @exclude

// n^3 solution
template <typename T>
bool check_ans(const vector<T> &A, const T &t) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) {
      for (int k = 0; k < A.size(); ++k) {
        if (A[i] + A[j] + A[k] == t) {
          return true;
        }
      }
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, T;
    if (argc == 2) {
      n = atoi(argv[1]);
      T = rand() % n;
    } else {
      n = 1 + rand() % 10000;
      T = rand() % n;
    }
    vector<int> A;
    for (size_t i = 0; i < n; ++i) {
      A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % 100000);
    }
    cout << boolalpha << has_3_sum(A, T) << endl;
    assert(check_ans(A, T) == has_3_sum(A, T));
  }
  return 0;
}
