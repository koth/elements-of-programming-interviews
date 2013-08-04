// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::queue;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

void print_matrix(const vector<deque<bool>> &A) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
}

// @include
void flip_color(vector<deque<bool>> *A, int x, int y) {
  const array<array<int, 2>, 4> dir = {{{{0, 1}}, {{0, -1}},
                                        {{1, 0}}, {{-1, 0}}}};
  const bool color = (*A)[x][y];

  queue<pair<int, int>> q;
  q.emplace(x, y);
  while (q.empty() == false) {
    pair<int, int> curr(q.front());
    (*A)[curr.first][curr.second] = !(*A)[curr.first][curr.second];  // flip
    for (const auto &d : dir) {
      pair<int, int> next(curr.first + d[0], curr.second + d[1]);
      if (next.first >= 0 && next.first < A->size() &&
          next.second >= 0 && next.second < (*A)[next.first].size() &&
          (*A)[next.first][next.second] == color) {
        q.emplace(next);
      }
    }
    q.pop();
  }
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  default_random_engine gen((random_device())());
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 100);
    n = dis(gen);
  }
  vector<deque<bool>> A(n, deque<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      uniform_int_distribution<int> zero_or_one(0, 1);
      A[i][j] = zero_or_one(gen);
    }
  }
  uniform_int_distribution<int> dis(0, n - 1);
  int i = dis(gen), j = dis(gen);
  cout << "color = " << i << ' ' << j << ' ' << A[i][j] << endl;
  print_matrix(A);
  flip_color(&A, i, j);
  cout << endl;
  print_matrix(A);
  return 0;
}
