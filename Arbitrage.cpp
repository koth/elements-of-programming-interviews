#include <iostream>
#include <cassert>
#include <limits>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// @include
bool Bellman_Ford(const vector<vector<double> > &G, const int &source) {
  vector<double> dis_to_source(G.size(), numeric_limits<double>::max());
  dis_to_source[source] = 0;

  for (int times = 1; times < G.size(); ++times) {
    bool have_update = false;
    for (int i = 0; i < G.size(); ++i) {
      for (int j = 0; j < G.size(); ++j) {
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
    for (int j = 0; j < G.size(); ++j) {
      if (dis_to_source[i] != numeric_limits<double>::max() &&
          dis_to_source[j] > dis_to_source[i] + G[i][j]) {
        return true;
      }
    }
  }
  return false;
}

bool is_Arbitrage_exist(vector<vector<double> > G) {
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
  srand(time(nullptr));
  int n, m;
  if (argc == 2) {
    n = atoi(argv[1]);
    m = 1 + rand() % (n * (n - 1) / 2);
  } else if (argc == 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
  } else {
    n = 1 + rand() % 100;
    m = 1 + rand() % (n * (n - 1) / 2);
  }
  vector<vector<double> > G(n, vector<double>(n));
  // Assume the input is a complete graph
  for (int i = 0; i < G.size(); ++i) {
    G[i][i] = 1;
    for (int j = i + 1; j < G.size(); ++j) {
      G[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
      G[j][i] = 1.0 / G[i][j];
    }
  }
  bool res = is_Arbitrage_exist(G);
  cout << boolalpha << res << endl;
  vector<vector<double> > g(3, vector<double>(3));
  for (int i = 0; i < 3; ++i) {
    g[i][i] = 1;
  }
  g[0][1] = 2, g[1][0] = 0.5, g[0][2] = g[2][0] = 1, g[1][2] = 4, g[2][1] = 0.25;
  res = is_Arbitrage_exist(g);
  assert(res == true);
  cout << boolalpha << is_Arbitrage_exist(g) << endl;
  /*
  vector<vector<bool> > have_edges(n, vector<bool>(n, false));
  for (int i = 0; i < m; ++i) {
    int a, b;
    do {
      a = rand() % n, b = rand() % n;
    } while (a == b || have_edges[a][b] == true);
    have_edges[a][b] = have_edges[b][a] = true;
  }
  */
  return 0;
}
