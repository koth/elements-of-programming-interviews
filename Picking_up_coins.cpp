// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

int pick_up_coins_helper(const vector<int>& C,
                         int a,
                         int b,
                         vector<vector<int>>* T);

// @include
int pick_up_coins(const vector<int>& C) {
  vector<vector<int>> T(C.size(), vector<int>(C.size(), -1));
  return pick_up_coins_helper(C, 0, C.size() - 1, &T);
}

int pick_up_coins_helper(const vector<int>& C,
                         int a,
                         int b,
                         vector<vector<int>>* T) {
  if (a > b) {
    return 0;  // base condition.
  }

  if ((*T)[a][b] == -1) {
    (*T)[a][b] = max(C[a] + min(pick_up_coins_helper(C, a + 2, b, T),
                                pick_up_coins_helper(C, a + 1, b - 1, T)),
                     C[b] + min(pick_up_coins_helper(C, a + 1, b - 1, T),
                                pick_up_coins_helper(C, a, b - 2, T)));
  }
  return (*T)[a][b];
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  vector<int> C;
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      C.emplace_back(atoi(argv[i]));
    }
  } else {
    uniform_int_distribution<int> dis(1, 1000);
    C.resize(dis(gen));
    for (int i = 0; i < C.size(); ++i) {
      uniform_int_distribution<int> dis(0, 99);
      C[i] = dis(gen);
    }
  }
  for (size_t i = 0; i < C.size(); ++i) {
    cout << C[i] << ' ';
  }
  cout << endl;
  cout << pick_up_coins(C) << endl;
  return 0;
}
