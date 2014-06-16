// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

void n_queens_helper(int n, int row, vector<int>* col_placement,
                     vector<vector<string>>* res);
bool is_feasible(const vector<int>& col_placement, int row);

// @include
vector<vector<string>> n_queens(int n) {
  vector<int> placement(n);
  vector<vector<string>> res;
  n_queens_helper(n, 0, &placement, &res);
  return res;
}

void n_queens_helper(int n, int row, vector<int>* col_placement,
                     vector<vector<string>>* res) {
  if (row == n) {
    vector<string> sol;
    for (int row = 0; row < col_placement->size(); ++row) {
      string line(n, '.');
      line[(*col_placement)[row]] = 'Q';
      sol.emplace_back(move(line));
    }
    res->emplace_back(move(sol));
  } else {
    for (int col = 0; col < n; ++col) {
      (*col_placement)[row] = col;
      if (is_feasible(*col_placement, row)) {
        n_queens_helper(n, row + 1, col_placement, res);
      }
    }
  }
}

bool is_feasible(const vector<int>& col_placement, int row) {
  for (int i = 0; i < row; ++i) {
    int diff = abs(col_placement[i] - col_placement[row]);
    if (diff == 0 || diff == row - i) {
      return false;
    }
  }
  return true;
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 15);
    n = dis(gen);
  }
  cout << "n = " << n << endl;
  auto res = n_queens(n);
  for (const auto& vec : res) {
    for (const string& s : vec) {
      cout << s << endl;
    }
    cout << endl;
  }
  return 0;
}
