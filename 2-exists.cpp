#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
class GraphVertex {
  public:
    enum Color {white, gray, black} color;
    vector<GraphVertex*> edges;
    // @exclude
    GraphVertex(void) : color(white) {}
    // @include
};

bool DFS(GraphVertex* cur, const GraphVertex* pre) {
  // Visiting a gray vertex means a cycle
  if (cur->color == GraphVertex::gray) {
    return true;
  }

  cur->color = GraphVertex::gray;  // marks current vertex as a gray one
  // Traverse the neighbor vertices
  for (GraphVertex* &next : cur->edges) {
    if (next != pre && next->color != GraphVertex::black) {
      if (DFS(next, cur)) {
        return true;
      }
    }
  }
  cur->color = GraphVertex::black;  // marks current vertex as black
  return false;
}

bool is_graph_2_exist(vector<GraphVertex> &G) {
  if (G.empty() == false) {
    return DFS(&G[0], nullptr);
  }
  return false;
}
// @exclude

void DFS_exclusion(GraphVertex* cur, GraphVertex* a, GraphVertex* b) {
  cur->color = GraphVertex::black;
  for (GraphVertex* &next : cur->edges) {
    if (next->color == GraphVertex::white && ((cur != a && cur != b) || (next != a && next != b))) {
      DFS_exclusion(next, a, b);
    }
  }
}

// O(n^2) check answer
bool check_answer(vector<GraphVertex> &G) {
  // marks all vertices as white
  for (GraphVertex &n : G) {
    n.color = GraphVertex::white;
  }

  for (GraphVertex &g : G) {
    for (GraphVertex* &t : g.edges) {
      DFS_exclusion(&g, &g, t);
      int count = 0;
      for (GraphVertex &n : G) {
        if (n.color == GraphVertex::black) {
          ++count;
          n.color = GraphVertex::white;
        }
      }
      if (count == G.size()) {
        return true;
      }
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 9000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 2 + rand() % 2000;
    }
    vector<GraphVertex> G(n);
    int m = 1 + rand() % (n * (n - 1) / 2);
    vector<vector<bool> > is_edge_exist(n, vector<bool>(n, false));
    // Make the graph become connected
    for (int i = 1; i < n; ++i) {
      G[i - 1].edges.emplace_back(&G[i]);
      G[i].edges.emplace_back(&G[i - 1]);
      is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
    }
    // Generate edges randomly
    m -= (n - 1);
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
    bool res = is_graph_2_exist(G);
    cout << boolalpha << res << endl;
    assert(check_answer(G) == res);
  }
  return 0;
}
