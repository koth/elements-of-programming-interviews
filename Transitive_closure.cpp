#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
class GraphVertex {
  public:
    int visitTime;
    vector<GraphVertex*> edges, extendedContacts;
    // @exclude
    GraphVertex(void) : visitTime(-1) {}
    // @include
};

void DFS(GraphVertex* cur, const int &time, vector<GraphVertex*> &contacts) {
  for (GraphVertex* &next : cur->edges) {
    if (next->visitTime != time) {
      next->visitTime = time;
      contacts.emplace_back(next);
      DFS(next, time, contacts);
    }
  }
}

void transitive_closure(vector<GraphVertex> &G) {
  // Build extended contacts for each vertex
  for (int i = 0; i < G.size(); ++i) {
    if (G[i].visitTime != i) {
      G[i].visitTime = i;
      DFS(&G[i], i, G[i].extendedContacts);
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  vector<GraphVertex> G;
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 1000;
  }
  fill_n(back_inserter(G), n, GraphVertex());
  cout << G.size() << endl;
  int m = 1 + rand() % (n * (n - 1) / 2);
  //cout << n << " " << m << endl;
  vector<vector<bool> > is_edge_exist(n, vector<bool>(n, false));
  /*
  // Make the graph become connected
  for (int i = 1; i < n; ++i) {
  G[i - 1].edges.emplace_back(i);
  G[i].edges.emplace_back(i - 1);
  is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
  }
   */

  // Generate edges randomly
  while (m-- > 0) {
    int a, b;
    do {
      a = rand() % n, b = rand() % n;
    } while (a == b || is_edge_exist[a][b] == true);
    //cout << a << " " << b << endl;
    is_edge_exist[a][b] = is_edge_exist[b][a] = true;
    G[a].edges.emplace_back(&G[b]);
    G[b].edges.emplace_back(&G[a]);
  }

  transitive_closure(G);
  /*
  for (int i = 0; i < G.size(); ++i) {
    cout << i << endl << '\t';
    for (GraphVertex* &e : G[i].extendedContacts) {
      cout << e << ' ';
    }
    cout << endl;
  }
  for (int i = 0; i < G.size(); ++i) {
    cout << i << endl;
    for (int j = 0; j < G[i].edges.size(); ++j) {
      cout << ' ' << G[i].edges[j];
    }
    cout << endl;
  }
  //*/
  return 0;
}
