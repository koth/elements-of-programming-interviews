#include <iostream>
#include <limits>
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
      for (int c = a; c < A.size(); ++c) {
        for (int d = b; d < A[c].size(); ++d) {
          bool all_1 = true;
          int count = 0;
          for (int i = a; i <= c; ++i) {
            for (int j = b; j <= d; ++j) {
              if (A[i][j] == false) {
                all_1 = false;
                count = 0;
                break;
              } else {
                ++count;
              }
            }
            if (all_1 == false) {
              break;
            }
          }
          if (all_1 == true && count > max) {
            max = count;
          }
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

int max_rectangle_submatrix(const vector<vector<bool> > &A) {
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

  int max_rect_area = 0;
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      // Process (i, j) if it is feasible and is possible to update
      // max_rect_area
      if (A[i][j] && table[i][j].w * table[i][j].h > max_rect_area) {
        int min_width = numeric_limits<int>::max();
        for (int a = 0; a < table[i][j].h; ++a) {
          min_width = min(min_width, table[i + a][j].w);
          max_rect_area = max(max_rect_area, min_width * (a + 1));
        }
      }
    }
  }
  return max_rect_area;
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
    cout << max_rectangle_submatrix(A) << endl;
    cout << check_ans(A) << endl;
    assert(check_ans(A) == max_rectangle_submatrix(A));
  }
  return 0;
}
