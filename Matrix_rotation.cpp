// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

void print_matrix(const vector<vector<int>>& A) {
  for (size_t i = 0; i < A.size(); ++i) {
    copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
}

void check_answer(const vector<vector<int>>& A) {
  int k = 1;
  for (int j = A.size() - 1; j >= 0; --j) {
    for (size_t i = 0; i < A.size(); ++i) {
      assert(k++ == A[i][j]);
    }
  }
}

void rotate_matrix_helper(vector<vector<int>>* A, int x_s, int x_e, int y_s,
                          int y_e);
void copy_matrix(vector<vector<int>>* A, int A_x_s, int A_x_e, int A_y_s,
                 int A_y_e, const vector<vector<int>>& S, int S_x, int S_y);

// @include
void rotate_matrix(vector<vector<int>>* A) {
  rotate_matrix_helper(A, 0, A->size(), 0, A->size());
}

void rotate_matrix_helper(vector<vector<int>>* A, int x_s, int x_e, int y_s,
                          int y_e) {
  if (x_e > x_s + 1) {
    int mid_x = x_s + ((x_e - x_s) >> 1), mid_y = y_s + ((y_e - y_s) >> 1);
    // Move submatrices.
    vector<vector<int>> C(mid_x - x_s, vector<int>(mid_y - y_s));
    copy_matrix(&C, 0, C.size(), 0, C.size(), *A, x_s, y_s);
    copy_matrix(A, x_s, mid_x, y_s, mid_y, *A, mid_x, y_s);
    copy_matrix(A, mid_x, x_e, y_s, mid_y, *A, mid_x, mid_y);
    copy_matrix(A, mid_x, x_e, mid_y, y_e, *A, x_s, mid_y);
    copy_matrix(A, x_s, mid_x, mid_y, y_e, C, 0, 0);

    // Recursively rotate submatrices.
    rotate_matrix_helper(A, x_s, mid_x, y_s, mid_y);
    rotate_matrix_helper(A, x_s, mid_x, mid_y, y_e);
    rotate_matrix_helper(A, mid_x, x_e, mid_y, y_e);
    rotate_matrix_helper(A, mid_x, x_e, y_s, mid_y);
  }
}

void copy_matrix(vector<vector<int>>* A, int A_x_s, int A_x_e, int A_y_s,
                 int A_y_e, const vector<vector<int>>& S, int S_x, int S_y) {
  for (int i = 0; i < A_x_e - A_x_s; ++i) {
    copy(S[S_x + i].cbegin() + S_y, S[S_x + i].cbegin() + S_y + A_y_e - A_y_s,
         (*A)[A_x_s + i].begin() + A_y_s);
  }
}
// @exclude

int main(int argc, char* argv[]) {
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
    vector<vector<int>> A(1 << n, vector<int>(1 << n));
    int k = 1;
    for (size_t i = 0; i < A.size(); ++i) {
      for (size_t j = 0; j < A[i].size(); ++j) {
        A[i][j] = k++;
      }
    }
    rotate_matrix(&A);
    check_answer(A);
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    for (int times = 0; times < 100; ++times) {
      n = dis(gen);
      vector<vector<int>> A(1 << n, vector<int>(1 << n));
      int k = 1;
      for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
          A[i][j] = k++;
        }
      }
      // print_matrix(A);
      rotate_matrix(&A);
      check_answer(A);
      // print_matrix(A);
    }
  }
  return 0;
}
