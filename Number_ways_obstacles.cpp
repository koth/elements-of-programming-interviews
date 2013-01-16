#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
// Given the dimensions of A, n and m, and B, return the number of ways
// from A[0][0] to A[n - 1][m - 1] considering obstacles
int number_of_ways_with_obstacles(const int &n, const int &m, 
                                  const vector<vector<bool> > &B) {
  vector<vector<int> > A(n, vector<int>(m, 0));
  // No way to start from (0, 0) if B[0][0] == true
  A[0][0] = !B[0][0];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (B[i][j] == 0) {
        A[i][j] += (i - 1 < 0 ? 0 : A[i - 1][j]) +
                   (j - 1 < 0 ? 0 : A[i][j - 1]);
      }
    }
  }
  return A.back().back();
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, m;
  if (argc == 3) {
    n = atoi(argv[1]), m = atoi(argv[2]);
  } else {
    n = 1 + (rand() % 10);
    m = 1 + (rand() % 10);
  }
  vector<vector<bool> > B(n, vector<bool>(m));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      int x = rand() % 10;
      B[i][j] = ((x < 2) ? 1 : 0);
    }
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      cout << B[i][j] << ' ';
    }
    cout << endl;
  }
  cout << number_of_ways_with_obstacles(n, m, B) << endl;
  return 0;
}
