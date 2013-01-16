#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
void print_matrix_spiral(vector<vector<int> > A) {
  const array<array<int, 2>, 4> shift = {0, 1, 1, 0, 0, -1, -1, 0};
  int dir = 0, x = 0, y = 0;

  for (int i = 0; i < A.size() * A.size(); ++i) {
    cout << A[x][y] << ' ';
    A[x][y] = 0;
    int nx = x + shift[dir][0], ny = y + shift[dir][1];
    if (nx < 0 || nx >= A.size() || ny < 0 || ny >= A.size() ||
        A[nx][ny] == 0) {
      dir = (dir + 1) & 3;
      nx = x + shift[dir][0], ny = y + shift[dir][1];
    }
    x = nx, y = ny;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int N;
  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    N = 1 + rand() % 50;
  }
  vector<vector<int> > A(N, vector<int>(N));
  int x = 1;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      A[i][j] = x++;
    }
  }
  print_matrix_spiral(A);
  return 0;
}
