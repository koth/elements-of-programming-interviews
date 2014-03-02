// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int compute_binomial_coefficients(int n, int k) {
  array<vector<int>, 2> table = {vector<int>(k + 1), vector<int>(k + 1)};
  table[0][0] = 1;
  // C(i, j) = C(i - 1, j) + C(i - 1, j - 1).
  for (int i = 1; i <= n; ++i) {
    table[i & 1][0] = 1;  // special case: one way to select zero element.
    for (int j = 1; j <= i && j <= k; ++j) {
      table[i & 1][j] = table[(i - 1) & 1][j] + table[(i - 1) & 1][j - 1];
    }
  }
  return table[n & 1][k];
}
// @exclude

int check_ans(int n, int k) {
  vector<int> number;
  for (int i = 0; i < k; ++i) {
    number.emplace_back(n - i);
  }

  vector<int> temp;
  for (int i = 2; i <= k; ++i) {
    bool find = false;
    for (int& a : number) {
      if ((a % i) == 0) {
        a /= i;
        find = true;
        break;
      }
    }
    if (find == false) {
      temp.emplace_back(i);
    }
  }

  int res = 1;
  for (const int& a : number) {
    res *= a;
  }

  for (const int& a : temp) {
    res /= a;
  }

  return res;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 21);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(0, n);
      k = k_dis(gen);
    }

    int res = compute_binomial_coefficients(n, k);
    cout << "res = " << res << endl;
    assert(res == check_ans(n, k));
    cout << n << " out of " << k << " = " << res << endl;
    if (argc == 3) {
      break;
    }
  }
  return 0;
}
