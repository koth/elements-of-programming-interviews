// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <vector>

using std::vector;

// @include
template <typename T>
vector<T> intersect_arrs3(const vector<T> &A, const vector<T> &B) {
  vector<T> intersect;
  int i = 0, j = 0;
  while (i < A.size() && j < B.size()) {
    if (A[i] == B[j] && (i == 0 || A[i] != A[i - 1])) {
      intersect.emplace_back(A[i]);
      ++i, ++j;
    } else if (A[i] < B[j]) {
      ++i;
    } else {  // A[i] > B[j]
      ++j;
    }
  }
  return intersect;
}
// @exclude
