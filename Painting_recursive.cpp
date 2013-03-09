#include <iostream>
#include <array>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

void print_matrix(vector<vector<bool>> &A) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
}

// @include
void flip_color(vector<vector<bool>> &A, const int &x, const int &y) {
  const array<array<int, 2>, 4> dir = {-1, 0, 1, 0, 0, -1, 0, 1};
  const bool color = A[x][y];
  A[x][y] = !A[x][y];  // flip the color

  for (auto &d : dir) {
    const int nx = x + d[0], ny = y + d[1];
    if (nx >= 0 && nx < A.size() && ny >= 0 && ny < A[nx].size() &&
        A[nx][ny] == color) {
      flip_color(A, nx, ny);
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }
  vector<vector<bool>> A(n, vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      A[i][j] = rand() & 1;
    }
  }
  int i = rand() % n, j = rand() % n;
  cout << "color = " << i << ' ' << j << ' ' << A[i][j] << endl;
  print_matrix(A);
  flip_color(A, i, j);
  cout << endl;
  print_matrix(A);
  return 0;
}
