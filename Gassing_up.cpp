// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int find_start_city(const vector<int>& G, const vector<int>& D) {
  int carry = 0;
  pair<int, int> min(0, 0);
  for (int i = 1; i < G.size(); ++i) {
    carry += G[i - 1] - D[i - 1];
    if (carry < min.second) {
      min = {i, carry};
    }
  }
  return min.first;
}
// @exclude

void check_ans(const vector<int>& G, const vector<int>& D, int c) {
  int s = c;
  int gas = 0;
  do {
    gas += G[s] - D[s];
    assert(gas >= 0);
    s = (s + 1) % G.size();
  } while (s != c);
}

void small_test() {
  // Example in the book.
  vector<int> G = {20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25};
  vector<int> D = {15, 20, 50, 15, 15, 30, 20, 55, 20, 50, 10, 15, 15};
  assert(8 == find_start_city(G, D));
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> G, D;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(1, 200);
      int x = dis(gen);
      sum += x;
      G.emplace_back(x);
    }
    sum -= n;
    for (int i = 0; i < n; ++i) {
      int x = 0;
      if (sum) {
        uniform_int_distribution<int> dis(1, sum);
        x = dis(gen);
      }
      D.emplace_back(x + 1);
      sum -= x;
    }
    D.back() += sum;
    /*
    for (int i = 0; i < n; ++i) {
      cout << G[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
      cout << D[i] << ' ';
    }
    cout << endl;
    */
    int c = find_start_city(G, D);
    cout << "start city = " << c << endl;
    check_ans(G, D, c);
  }
  return 0;
}
