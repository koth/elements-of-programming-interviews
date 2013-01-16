#include <iostream>
#include <utility>
#include <queue>
#include <limits>
#include <cassert>
#include <vector>

using namespace std;

// @include
template <typename DistanceType>
class GraphVertex {
  public:
    pair<DistanceType, int> distance;  // stores (dis, #edges) pair
    // stores (vertex, dis) pair
    vector<pair<GraphVertex<DistanceType>*, DistanceType> > edges;
    int id;  // stores the id of this vertex
    GraphVertex* pred;  // stores the predecessor in the shortest path
    bool visited;

    GraphVertex(void) :
      distance(numeric_limits<DistanceType>::max(), 0),
      pred(nullptr),
      visited(false) {}
};

template <typename DistanceType>
class Compare {
  public:
    const bool operator()(const GraphVertex<DistanceType>* lhs,
                          const GraphVertex<DistanceType>* rhs) const { 
      return lhs->distance.first > rhs->distance.first ||
             (lhs->distance.first == rhs->distance.first &&
              lhs->distance.second > rhs->distance.second);
    }
};

template <typename DistanceType>
void output_shortest_path(GraphVertex<DistanceType>* &v) {
  if (v) {
    output_shortest_path(v->pred);
    cout << v->id << " ";
  }
}

template <typename DistanceType>
void Dijkstra_shortest_path(vector<GraphVertex<DistanceType> > &G,
                            GraphVertex<DistanceType>* s, 
                            GraphVertex<DistanceType>* t) {
  // Initialization
  s->distance = {0, 0};
  priority_queue<
    GraphVertex<DistanceType>*,
    vector<GraphVertex<DistanceType>* >,
    Compare<DistanceType> > min_heap;
  min_heap.emplace(s);

  do {
    // Extract the minimum distance vertex from heap
    GraphVertex<DistanceType>* u = nullptr;
    while (min_heap.empty() == false) {
      u = min_heap.top();
      min_heap.pop();
      if (u->visited == false) {
        break;
      }
    }

    if (u) {  // u is a valid vertex
      u->visited = true;
      // Relax neighboring vertices of u
      for (const auto &v : u->edges) {
        pair<DistanceType, int> v_distance =
          {u->distance.first + v.second, u->distance.second + 1};
        if (v.first->distance.first > v_distance.first ||
            (v.first->distance.first == v_distance.first &&
             v.first->distance.second > v_distance.second)) {
          v.first->pred = u, v.first->distance = v_distance;
          min_heap.emplace(v.first);
        }
      }
    } else {  // u is not a valid vertex
      break;
    }
  } while (t->visited == false);

  // Output the shortest path with fewest edges
  output_shortest_path(t);
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 2 + rand() % 1000;
  }
  vector<GraphVertex<int> > G;
  for (int i = 0; i < n; ++i) {
    G.emplace_back(GraphVertex<int>());
  }
  int m = 1 + rand() % (n * (n - 1) / 2);
  vector<vector<bool> > is_edge_exist(n, vector<bool>(n, false));
  // Make the graph become connected
  for (int i = 1; i < n; ++i) {
    int len = 1 + rand() % 100;
    G[i - 1].edges.emplace_back(&G[i], len);
    G[i].edges.emplace_back(&G[i - 1], len);
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
    int len = 1 + rand() % 100;
    G[a].edges.emplace_back(&G[b], len);
    G[b].edges.emplace_back(&G[a], len);
  }
  int s = rand() % n, t = rand() % n;
  for (int i = 0; i < G.size(); ++i) {
    G[i].id = i;
    for (const pair<GraphVertex<int>*, int> e : G[i].edges) {
      cout << (e.first - &G[0]) << ' ' << e.second << ',';
    }
    cout << endl;
  }
  cout << "source = " << s << ", terminal = " << t << endl;
  Dijkstra_shortest_path(G, &G[s], &G[t]);
  cout << endl << G[t].distance.first << " " << G[t].distance.second << endl;
  return 0;
}
