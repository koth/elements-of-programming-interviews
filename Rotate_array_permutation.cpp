// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./GCD.h"

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

vector<int> rand_vector(int len) {
  vector<int> ret;
  while (len--) {
    ret.emplace_back(rand());
  }
  return ret;
}

// @include
template <typename T>
void rotate_array(vector<T>* A, size_t i) {
  i %= A->size();
  int cycles = GCD(A->size(), i);  // number of cycles in this rotation
  int hops = A->size() / cycles;  // number of elements in a cycle

  for (int c = 0; c < cycles; ++c) {
    T temp = (*A)[c];
    for (int j = 1; j < hops; ++j) {
      swap((*A)[(c + j * i) % A->size()], temp);
    }
    (*A)[c] = temp;
  }
}
// @exclude

template <typename T>
void check_answer(vector<T> &A, const size_t &i, vector<T> &rotated) {
  assert(A.size() == rotated.size());
  for (size_t idx = 0; idx < A.size(); ++idx) {
    assert(rotated[(idx + i) % rotated.size()] == A[idx]);
  }
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int len;
    if (argc == 2) {
      len = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      len = dis(gen);
    }
    vector<int> A(rand_vector(len));
    uniform_int_distribution<int> dis(0, len - 1);
    size_t i = dis(gen);
    vector<int> B(A);
    rotate_array(&B, i);
    check_answer(A, i, B);
  }
  return 0;
}
