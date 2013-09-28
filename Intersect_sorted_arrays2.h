// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_
#define SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_

#include <algorithm>
#include <vector>

using std::vector;

// @include
vector<int> intersect_arrs2(const vector<int>& A, const vector<int>& B) {
  vector<int> intersect;
  for (int i = 0; i < A.size(); ++i) {
    if ((i == 0 || A[i] != A[i - 1]) &&
        binary_search(B.cbegin(), B.cend(), A[i])) {
      intersect.emplace_back(A[i]);
    }
  }
  return intersect;
}
// @exclude
#endif  // SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_
