// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_
#define SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_

#include <vector>

using std::vector;

// @include
template <typename T>
vector<T> intersect_arrs1(const vector<T> &A, const vector<T> &B) {
  vector<T> intersect;
  for (int i = 0; i < A.size(); ++i) {
    if (i == 0 || A[i] != A[i - 1]) {
      for (int j = 0; j < B.size(); ++j) {
        if (A[i] == B[j]) {
          intersect.emplace_back(A[i]);
          break;
        }
      }
    }
  }
  return intersect;
}
// @exclude
#endif  // SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_
