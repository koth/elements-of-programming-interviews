// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int count_combinations(int k, const vector<int>& score_ways) {
  vector<int> combinations(k + 1, 0);
  combinations[0] = 1;  // one way to reach 0.
  for (const int& score : score_ways) {
    for (int j = score; j <= k; ++j) {
      combinations[j] += combinations[j - score];
    }
  }
  return combinations[k];
}
// @exclude

void simple_test() {
  vector<int> score_ways = {2, 3, 7};
  assert(4 == count_combinations(12, score_ways));
  assert(1 == count_combinations(5, score_ways));
}

int main(int argc, char* argv[]) {
  simple_test();
  default_random_engine gen((random_device())());
  int k;
  vector<int> score_ways;
  if (argc == 1) {
    uniform_int_distribution<int> k_dis(0, 999);
    k = k_dis(gen);
    uniform_int_distribution<int> size_dis(1, 50);
    score_ways.resize(size_dis(gen));
    for (int i = 0; i < score_ways.size(); ++i) {
      uniform_int_distribution<int> score_dis(1, 1000);
      score_ways[i] = score_dis(gen);
    }
  } else if (argc == 2) {
    k = atoi(argv[1]);
    uniform_int_distribution<int> size_dis(1, 50);
    score_ways.resize(size_dis(gen));
    for (int i = 0; i < score_ways.size(); ++i) {
      uniform_int_distribution<int> score_dis(1, 1000);
      score_ways[i] = score_dis(gen);
    }
  } else {
    k = atoi(argv[1]);
    for (int i = 2; i < argc; ++i) {
      score_ways.emplace_back(atoi(argv[i]));
    }
  }
  cout << count_combinations(k, score_ways) << endl;
  return 0;
}
