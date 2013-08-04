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
using std::swap;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
void rearrange(vector<T> *A) {
  for (int i = 0; i < A->size() - 1; ++i) {
    if ((i & 1 && (*A)[i] < (*A)[i + 1]) ||
        ((i & 1) == 0 && (*A)[i] > (*A)[i + 1])) {
      swap((*A)[i], (*A)[i + 1]);
    }
  }
}
// @exclude

template <typename T>
void check_answer(const vector<T> &A) {
  for (int i = 0; i < A.size(); ++i) {
    if (i & 1) {
      assert(A[i] >= A[i - 1]);
      if (i < A.size() - 1) {
        assert(A[i] >= A[i + 1]);
      }
    } else {
      if (i > 0) {
        assert(A[i - 1] >= A[i]);
      }
      if (i < A.size() - 1) {
        assert(A[i + 1] >= A[i]);
      }
    }
  }
}

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
    uniform_int_distribution<int> dis(-n, n);
    for (int i = 0; i < n; ++i) {
      A.emplace_back(dis(gen));
    }
    rearrange(&A);
    /*
    for (const int &a : A) {
      cout << a << ' ';
    }
    cout << endl;
    */
    check_answer(A);
  }
  return 0;
}
