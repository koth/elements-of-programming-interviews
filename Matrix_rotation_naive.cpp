// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

template <typename T>
void print_matrix(const vector<vector<T>> &A) {
  for (int i = 0; i < A.size(); ++i) {
    // copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
    for ( int j = 0 ; j < A.size(); ++j) {
      cout << "A[" << i << "," << j << "] = " << A[i][j] << "  ";
    }
    cout << endl;
  }
}

template <typename T>
void check_answer(const vector<vector<T>> &A) {
  int k = 1;
  for (int j = A.size() - 1; j >= 0; --j) {
    for (int i = 0; i < A.size(); ++i) {
      assert(k++ == A[i][j]);
    }
  }
}

// @include
template <typename T>
void rotate_matrix(vector<vector<T>>* A) {
  for (int i = 0; i < (A->size() >> 1); ++i) {
    for (int j = i; j < A->size() - i - 1; ++j) {
      T temp = (*A)[i][j];
      (*A)[i][j] = (*A)[A->size() - 1 - j][i];
      (*A)[A->size() - 1 - j][i] = (*A)[A->size() - 1 - i][A->size() - 1 - j];
      (*A)[A->size() - 1 - i][A->size() - 1 - j] = (*A)[j][A->size() - 1 - i];
      (*A)[j][A->size() - 1 - i] = temp;
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
    vector<vector<int>> A(1 << n, vector<int>(1 << n));
    int k = 1;
    for (int i = 0; i < A.size(); ++i) {
      for (int j = 0; j < A[i].size(); ++j) {
        A[i][j] = k++;
      }
    }
    print_matrix(A);
    rotate_matrix(A);
    check_answer(A);
    print_matrix(A);
  } else {
    srand(time(nullptr));
    for (int times = 0; times < 100; ++times) {
      n = 1 + rand() % 10;
      vector<vector<int>> A(1 << n, vector<int>(1 << n));
      int k = 1;
      for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
          A[i][j] = k++;
        }
      }
      //print_matrix(A);
      rotate_matrix(A);
      check_answer(A);
      //print_matrix(A);
    }
  }
  return 0;
}
