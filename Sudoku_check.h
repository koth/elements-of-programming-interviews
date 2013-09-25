// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_SUDOKU_CHECK_H_
#define SOLUTIONS_SUDOKU_CHECK_H_

#include <deque>
#include <vector>

using std::deque;
using std::vector;

// @include
// Check if a partially filled matrix has any conflicts.
bool is_valid_Sudoku(const vector<vector<int>>& A) {
  // Check row constraints.
  for (int i = 0; i < A.size(); ++i) {
    deque<bool> is_present(A.size() + 1, false);
    for (int j = 0; j < A.size(); ++j) {
      if (A[i][j] != 0 && is_present[A[i][j]] == true) {
        return false;
      } else {
        is_present[A[i][j]] = true;
      }
    }
  }

  // Check column constraints.
  for (int j = 0; j < A.size(); ++j) {
    deque<bool> is_present(A.size() + 1, false);
    for (int i = 0; i < A.size(); ++i) {
      if (A[i][j] != 0 && is_present[A[i][j]] == true) {
        return false;
      } else {
        is_present[A[i][j]] = true;
      }
    }
  }

  // Check region constraints.
  int region_size = sqrt(A.size());
  for (int I = 0; I < region_size; ++I) {
    for (int J = 0; J < region_size; ++J) {
      deque<bool> is_present(A.size() + 1, false);
      for (int i = 0; i < region_size; ++i) {
        for (int j = 0; j < region_size; ++j) {
          if (A[region_size * I + i][region_size * J + j] != 0 &&
              is_present[A[region_size * I + i][region_size * J + j]]) {
            return false;
          } else {
            is_present[A[region_size * I + i][region_size * J + j]] = true;
          }
        }
      }
    }
  }
  return true;
}
// @exclude
#endif  // SOLUTIONS_SUDOKU_CHECK_H_
