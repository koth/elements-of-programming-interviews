#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
class Constraint {
  public:
    int a, b;
};

class GraphVertex {
  public:
    int group;  // represents the connected component it belongs
    vector<GraphVertex*> edges;

    GraphVertex() : group(-1) {}
};

void DFS(GraphVertex &u) {
  for (GraphVertex* &v : u.edges) {
    if (v->group == -1) {
      v->group = u.group;
      DFS(*v);
    }
  }
}

bool are_constraints_satisfied(
  const vector<Constraint> &E,    // Equality constraints
  const vector<Constraint> &I) {  // Inequality constraints
  unordered_map<int, GraphVertex> G;
  // Build graph G according to E
  for (const Constraint &e : E) {
    G[e.a].edges.emplace_back(&G[e.b]), G[e.b].edges.emplace_back(&G[e.a]);
  }

  // Assign group index for each connected component
  int group_count = 0;
  for (pair<int, GraphVertex> vertex : G) {
    if (vertex.second.group == -1) {  // is a unvisited vertex
      vertex.second.group = group_count++;  // assigns a group index
      DFS(vertex.second);
    }
  }

  // Examine each inequality constraint to see if there is a violation
  for (const Constraint &i : I) {
    if (G[i.a].group == G[i.b].group) {
      return false;
    }
  }
  return true;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, m, k;
  if (argc == 2) {
    n = atoi(argv[1]);
    m = 1 + rand() % (n * (n - 1) / 2);
    k = 1 + rand() % ((n * (n - 1) / 2) - m);
  } else if (argc == 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    k = 1 + rand() % ((n * (n - 1) / 2) - m);
  } else {
    n = 2 + rand() % 100;
    m = 1 + rand() % (n * (n - 1) / 2);
    k = 1 + rand() % ((n * (n - 1) / 2) - m);
  }
  cout << "n = " << n << ", m = " << m << ", k = " << k << endl;
  vector<vector<bool> > have_edges(n, vector<bool>(n, false));
  vector<Constraint> E;
  for (int i = 0; i < m; ++i) {
    int a, b;
    do {
      a = rand() % n, b = rand() % n;
    } while (a == b || have_edges[a][b] == true);
    have_edges[a][b] = have_edges[b][a] = true;
    E.emplace_back(Constraint{a, b});
  }
  vector<Constraint> I;
  for (int i = 0; i < k; ++i) {
    int a, b;
    do {
      a = rand() % n, b = rand() %n;
    } while (a == b || have_edges[a][b] == true);
    have_edges[a][b] = have_edges[b][a] = true;
    I.emplace_back(Constraint{a, b});
  }
  //*
  cout << "equal constraint" << endl;
  for (const Constraint e : E) {
    cout << e.a << " " << e.b << endl;
  }
  cout << endl;
  cout << "inequal constraint" << endl;
  for (const Constraint i : I) {
    cout << i.a << " " << i.b << endl;
  }
  cout << endl;
  //*/
  bool res = are_constraints_satisfied(E, I);
  cout << boolalpha << res << endl;
  return 0;
}
