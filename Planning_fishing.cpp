#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
T maximize_fishing(vector<vector<T>> A) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      A[i][j] += max(i < 1 ? 0 : A[i - 1][j], j < 1 ? 0 : A[i][j - 1]);
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
    n = 1 + rand() % 100, m = 1 + rand() % 100;
  }
  vector<vector<int>> A(n, vector<int>(m));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      A[i][j] = rand() % 1000;
    }
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
  cout << maximize_fishing(A) << endl;
  return 0;
}
