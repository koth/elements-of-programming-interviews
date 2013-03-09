#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// @include
template <typename T>
bool matrix_search(const vector<vector<T>> &A, const T &x) {
  int r = 0, c = A[0].size() - 1;
  while (r < A.size() && c >= 0) {
    if (A[r][c] == x) {
      return true;
    } else if (A[r][c] < x) {
      ++r;
    } else {  // A[r][c] > x
      --c;
    }
  }
  return false;
}
// @exclude

// O(n^2) solution for verifying answer
template <typename T>
bool brute_force_search(const vector<vector<T>> &A, const T &x) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      if (A[i][j] == x) {
        return true;
      }
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      n = 1 + rand() % 100, m = 1 + rand() % 100;
    }
    vector<vector<int>> A(n, vector<int>(m));
    A[0][0] = rand() % 100;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int up = (i == 0) ? 0 : A[i - 1][j];
        int left = (j == 0) ? 0 : A[i][j - 1];
        A[i][j] = max(up, left) + 1 + rand() % 20;
      }
    }
    int x = rand() % 1000;
    assert(brute_force_search(A, x) == matrix_search(A, x));
  }
  return 0;
}
