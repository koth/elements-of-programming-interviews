#include <iostream>
#include <tuple>
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
    vector<pair<GraphVertex<DistanceType>*, DistanceType>> edges;
    int id;  // stores the id of this vertex
    GraphVertex* pred;  // stores the predecessor in the shortest path
    bool visited;

    GraphVertex(void) :
      distance(numeric_limits<DistanceType>::max(), 0),
      pred(nullptr),
      visited(false) {}
};

template <typename DistanceType, typename QData>
class Comp {
  public:
    const bool operator()(const QData &lhs, const QData &rhs) const {
      return get<1>(lhs) > get<1>(rhs) ||
             (get<1>(lhs) == get<1>(rhs) && get<2>(lhs) > get<2>(rhs));
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
void Dijkstra_shortest_path(vector<GraphVertex<DistanceType>> &G,
                            GraphVertex<DistanceType>* s,
                            GraphVertex<DistanceType>* t) {
  // Initialization
  s->distance = {0, 0};  // stores (dis, #edges) pair
  typedef tuple<GraphVertex<DistanceType>*, DistanceType, int> QData;
  priority_queue<QData, vector<QData>, Comp<DistanceType, QData>> min_heap;
  min_heap.emplace(s);

  do {
    // Extract the minimum distance vertex from heap
    QData u = {nullptr, 0, 0};
    while (min_heap.empty() == false) {
      u = min_heap.top();
      min_heap.pop();
      if (get<0>(u)->visited == false) {
        break;
      }
    }

    if (get<0>(u)) {  // u is a valid vertex
      get<0>(u)->visited = true;
      // Relax neighboring vertices of u
      for (const auto &v : get<0>(u)->edges) {
        DistanceType v_distance = get<1>(u) + v.second;
        int v_num_edges = get<2>(u) + 1;
        if (v.first->distance.first > v_distance ||
            (v.first->distance.first == v_distance &&
             v.first->distance.second > v_num_edges)) {
          v.first->pred = get<0>(u);
          v.first->distance = {v_distance, v_num_edges};
          min_heap.emplace(v.first, v_distance, v_num_edges);
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

// DBH test
void test() {
  vector<GraphVertex<int>> G;
  for (int i = 0; i < 9; ++i) {
    G.emplace_back(GraphVertex<int>());
    G[i].id = i;
  }

  // G[0] is the source node that connects to 8 other nodes
  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[1], 13)); // 0-1
  G[1].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 13)); // 1-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[2], 24)); // 0-2
  G[2].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 24)); // 2-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[3], 28)); // 0-3
  G[3].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 28)); // 3-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[4], 25)); // 0-4
  G[4].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 25)); // 4-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[5], 30)); // 0-5
  G[5].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 30)); // 5-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[6], 31)); // 0-6
  G[6].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 31)); // 6-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[7], 10)); // 0-7
  G[7].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 10)); // 7-0

  G[0].edges.push_back(pair<GraphVertex<int>*, int>(&G[8], 29)); // 0-8
  G[8].edges.push_back(pair<GraphVertex<int>*, int>(&G[0], 29)); // 8-0

  G[1].edges.push_back(pair<GraphVertex<int>*, int>(&G[8], 7));  // 1-8
  G[8].edges.push_back(pair<GraphVertex<int>*, int>(&G[1], 7));  // 8-1

  G[2].edges.push_back(pair<GraphVertex<int>*, int>(&G[8], 1));  // 2-8
  G[8].edges.push_back(pair<GraphVertex<int>*, int>(&G[2], 1));  // 8-2

  G[7].edges.push_back(pair<GraphVertex<int>*, int>(&G[8], 16)); // 7-8
  G[8].edges.push_back(pair<GraphVertex<int>*, int>(&G[7], 16)); // 8-7

  int s = 0; // Source is G[0]
  int t = 2; // Destination is G[2]

  // Minimum distance path should be:
  // G[0] => G[1] => G[8] => G[2],
  // distance is: 13 + 7 + 1 = 21.

  Dijkstra_shortest_path(G, &G[s], &G[t]);
  cout << endl << "Min distance: " << G[t].distance.first << endl;
  assert(G[t].distance.first == 21);
  cout << "Number of edges: " << G[t].distance.second << endl;
  assert(G[t].distance.second == 3);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 2 + rand() % 1000;
  }
  vector<GraphVertex<int>> G;
  for (int i = 0; i < n; ++i) {
    G.emplace_back(GraphVertex<int>());
  }
  int m = 1 + rand() % (n * (n - 1) / 2);
  vector<vector<bool>> is_edge_exist(n, vector<bool>(n, false));
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
  test();
  return 0;
}
