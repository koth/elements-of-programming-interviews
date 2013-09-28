// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

vector<int> rand_vector(int len) {
  vector<int> ret;
  default_random_engine gen((random_device())());
  while (len--) {
    uniform_int_distribution<int> dis(0, 99);
    ret.emplace_back(dis(gen));
  }
  return ret;
}

// @include
int knapsack(int w, const vector<pair<int, int>>& items) {
  vector<int> V(w + 1, 0);
  for (int i = 0; i < items.size(); ++i) {
    for (int j = w; j >= items[i].first; --j) {
      V[j] = max(V[j], V[j - items[i].first] + items[i].second);
    }
  }
  return V[w];
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  vector<int> weight, value;
  int n, W;
  if (argc == 1) {
    uniform_int_distribution<int> n_dis(1, 100);
    n = n_dis(gen);
    uniform_int_distribution<int> W_dis(1, 1000);
    W = W_dis(gen);
    weight = rand_vector(n), value = rand_vector(n);
  } else if (argc == 2) {
    n = atoi(argv[1]);
    uniform_int_distribution<int> W_dis(1, 1000);
    W = W_dis(gen);
    weight = rand_vector(n), value = rand_vector(n);
  } else {
    n = atoi(argv[1]);
    W = atoi(argv[2]);
    for (int i = 0; i < n; ++i) {
      weight.emplace_back(atoi(argv[3 + i]));
    }
    for (int i = 0; i < n; ++i) {
      value.emplace_back(atoi(argv[3 + i + n]));
    }
  }
  cout << "Weight: ";
  for (int i = 0; i < n; ++i) {
    cout << weight[i] << ' ';
  }
  cout << endl << "Value: ";
  for (int i = 0; i < n; ++i) {
    cout << value[i] << ' ';
  }
  cout << endl;
  vector<pair<int, int>> items;
  for (int i = 0; i < weight.size(); ++i) {
    items.emplace_back(weight[i], value[i]);
  }
  cout << "knapsack size = " << W << endl;
  cout << "all value = " << knapsack(W, items) << endl;
  return 0;
}
