// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

// @include
bool Bellman_Ford(const vector<vector<double>> &G, const int &source) {
  vector<double> dis_to_source(G.size(), numeric_limits<double>::max());
  dis_to_source[source] = 0;

  for (int times = 1; times < G.size(); ++times) {
    bool have_update = false;
    for (int i = 0; i < G.size(); ++i) {
      for (int j = 0; j < G[i].size(); ++j) {
        if (dis_to_source[i] != numeric_limits<double>::max() &&
            dis_to_source[j] > dis_to_source[i] + G[i][j]) {
          have_update = true;
          dis_to_source[j] = dis_to_source[i] + G[i][j];
        }
      }
    }

    // No update in this iteration means no negative cycle
    if (have_update == false) {
      return false;
    }
  }

  // Detect cycle if there is any further update
  for (int i = 0; i < G.size(); ++i) {
    for (int j = 0; j < G[i].size(); ++j) {
      if (dis_to_source[i] != numeric_limits<double>::max() &&
          dis_to_source[j] > dis_to_source[i] + G[i][j]) {
        return true;
      }
    }
  }
  return false;
}

bool is_Arbitrage_exist(vector<vector<double>> G) {
  // Transform each edge in G
  for (vector<double> &edge_list : G) {
    for (double &edge : edge_list) {
      edge = -log10(edge);
    }
  }

  // Use Bellman-Ford to find negative weight cycle
  return Bellman_Ford(G, 0);
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  int n, m;
  if (argc == 2) {
    n = atoi(argv[1]);
    uniform_int_distribution<int> m_dis(1, n * (n - 1) / 2);
    m = m_dis(gen);
  } else if (argc == 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
  } else {
    uniform_int_distribution<int> n_dis(1, 100);
    n = n_dis(gen);
    uniform_int_distribution<int> m_dis(1, n * (n - 1) / 2);
    m = m_dis(gen);
  }
  vector<vector<double>> G(n, vector<double>(n));
  // Assume the input is a complete graph
  for (int i = 0; i < G.size(); ++i) {
    G[i][i] = 1;
    for (int j = i + 1; j < G.size(); ++j) {
      uniform_real_distribution<double> dis(0, 1);
      G[i][j] = dis(gen);
      G[j][i] = 1.0 / G[i][j];
    }
  }
  bool res = is_Arbitrage_exist(G);
  cout << boolalpha << res << endl;
  vector<vector<double>> g(3, vector<double>(3));
  for (int i = 0; i < 3; ++i) {
    g[i][i] = 1;
  }
  g[0][1] = 2, g[1][0] = 0.5, g[0][2] = g[2][0] = 1,
  g[1][2] = 4, g[2][1] = 0.25;
  res = is_Arbitrage_exist(g);
  assert(res == true);
  cout << boolalpha << is_Arbitrage_exist(g) << endl;
  return 0;
}
