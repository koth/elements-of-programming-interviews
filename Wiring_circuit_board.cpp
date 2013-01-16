#include <iostream>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
class GraphVertex {
  public:
    int d;
    vector<GraphVertex*> edges;

    GraphVertex(void) : d(-1) {}
};

bool BFS(GraphVertex* s) {
  queue<GraphVertex*> q;
  q.emplace(s);

  while (q.empty() == false) {
    for (GraphVertex* &t : q.front()->edges) {
      if (t->d == -1) {  // unvisited vertex
        t->d = q.front()->d + 1;
        q.emplace(t);
      } else if (t->d == q.front()->d) {
        return false;
      }
    }
    q.pop();
  }
  return true;
}

bool is_any_placement_feasible(vector<GraphVertex> &G) {
  for (GraphVertex &v : G) {
    if (v.d == -1) {  // unvisited vertex
      v.d = 0;
      if (BFS(&v) == false) {
        return false;
      }
    }
  }
  return true;
}
// @exclude

bool DFS(GraphVertex* s) {
  for (GraphVertex* &t : s->edges) {
    if (t->d == -1) {
      t->d = !s->d;
      if (DFS(t) == false) {
        return false;
      }
    } else if (t->d == s->d) {
      return false;
    }
  }
  return true;
}

bool is_2_colorable(vector<GraphVertex> &G) {
  for (GraphVertex &v : G) {
    v.d = -1;
  }

  for (GraphVertex &v : G) {
    if (v.d == -1) {
      v.d = 0;
      if (DFS(&v) == false) {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 9000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 2 + rand() % 100;
    }
    vector<GraphVertex> G(n);
    int m = 1 + rand() % (n * (n - 1) / 2);
    cout << times << ' ' << n << ' ' << m << endl;
    vector<vector<bool> > is_edge_exist(n, vector<bool>(n, false));
    while (m-- > 0) {
      int a, b;
      do {
        a = rand() % n, b = rand() % n;
      } while (a == b || is_edge_exist[a][b] == true);
      is_edge_exist[a][b] = is_edge_exist[b][a] = true;
      G[a].edges.emplace_back(&G[b]);
      G[b].edges.emplace_back(&G[a]);
    }

    /*
    for (int i = 0; i < G.size(); ++i) {
      cout << i << endl;
      for (int j = 0; j < G[i].edges.size(); ++j) {
        cout << ' ' << G[i].edges[j];
      }
      cout << endl;
    }
    //*/
    bool res = is_any_placement_feasible(G);
    cout << boolalpha << res << endl;
    assert(res == is_2_colorable(G));
  }
  return 0;
}
