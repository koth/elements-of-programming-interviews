#include <iostream>
#include <cmath>
#include <array>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
void print_matrix_clockwise(const vector<vector<int>> &A, const int &offset) {
  if (offset == A.size() - offset - 1) {  // for matrix with odd size
    cout << A[offset][offset];
  }
  
  for (int j = offset; j < A.size() - offset - 1; ++j) {
    cout << A[offset][j] << ' ';
  }
  for (int i = offset; i < A.size() - offset - 1; ++i) {
    cout << A[i][A.size() - offset - 1] << ' ';
  }
  for (int j = A.size() - offset - 1; j > offset; --j) {
    cout << A[A.size() - offset - 1][j] << ' ';
  }
  for (int i = A.size() - offset - 1; i > offset; --i) {
    cout << A[i][offset] << ' ';
  }
}

void print_matrix_in_spiral_order(const vector<vector<int>> &A) {
  for (int offset = 0; offset < ceil(0.5 * A.size()); ++offset) {
    print_matrix_clockwise(A, offset);
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
  vector<vector<int>> A(N, vector<int>(N));
  int x = 1;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      A[i][j] = x++;
    }
  }
  print_matrix_in_spiral_order(A);
  return 0;
}
