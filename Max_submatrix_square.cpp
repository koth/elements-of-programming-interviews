#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

// O(m^3 n^3) time solution
int check_ans(const vector<vector<bool> > &A) {
  int max = 0;
  for (int a = 0; a < A.size(); ++a) {
    for (int b = 0; b < A[a].size(); ++b) {
      for (int r = 1; a + r <= A.size() && b + r <= A[0].size(); ++r) {
        int count = 0;
        bool all_1 = true;
        for (int c = a; c < a + r; ++c) {
          for (int d = b; d < b + r; ++d) {
            if (A[c][d]) {
              ++count;
            } else {
              all_1 = false;
              count = 0;
              break;
            }
          }
          if (all_1 == false) {
            break;
          }
        }
        if (count > max) {
          max = count;
        }
      }
    }
  }
  return max;
}

// @include
class MaxHW {
  public:
    int h, w;
};

int max_square_submatrix(const vector<vector<bool> > &A) {
  // DP table stores (h, w) for each (i, j)
  vector<vector<MaxHW> > table(A.size(), vector<MaxHW>(A[0].size()));

  for (int i = A.size() - 1; i >= 0; --i) {
    for (int j = A[i].size() - 1; j >= 0; --j) {
      table[i][j] = A[i][j] ?
        // Find the largest h such that (i, j) to (i + h, j) are feasible
        // Find the largest w such that (i, j) to (i, j + w) are feasible
        MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1,
              j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1} :
        MaxHW{0, 0};
    }
  }

  // A table stores the length of largest square for each (i, j)
  vector<vector<int> > s(A.size(), vector<int>(A[0].size(), 0));
  int max_square_area = 0;
  for (int i = A.size() - 1; i >= 0; --i) {
    for (int j = A[i].size() - 1; j >= 0; --j) {
      int side = min(table[i][j].h, table[i][j].w);
      if (A[i][j]) {
        // Get the length of largest square with bottom-left corner (i, j)
        if (i + 1 < A.size() && j + 1 < A[i + 1].size()) {
          side = min(s[i + 1][j + 1] + 1, side);
        }
        s[i][j] = side;
        max_square_area = max(max_square_area, side * side);
      }
    }
  }
  return max_square_area;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      n = 1 + rand() % 50, m = 1 + rand() % 50;
    }
    vector<vector<bool> > A(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        A[i][j] = (rand() & 1 ? true : false);
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << A[i][j] << ' ';
      }
      cout << endl;
    }
    cout << max_square_submatrix(A) << endl;
    cout << check_ans(A) << endl;
    assert(check_ans(A) == max_square_submatrix(A));
  }
  return 0;
}
