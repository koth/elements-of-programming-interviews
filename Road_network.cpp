#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
template <typename DistanceType>
class HighwaySection {
  public:
    int x, y;
    DistanceType distance;
};

template <typename DistanceType>
void Floyd_Warshall(vector<vector<DistanceType> > &G) {
  for (int k = 0; k < G.size(); ++k) {
    for (int i = 0; i < G.size(); ++i) {
      for (int j = 0; j < G.size(); ++j) {
        if (G[i][k] != numeric_limits<DistanceType>::max() &&
            G[k][j] != numeric_limits<DistanceType>::max() &&
            G[i][j] < G[i][k] + G[k][j]) {
          G[i][j] = G[i][k] + G[k][j];
        }
      }
    }
  }
}

template <typename DistanceType>
HighwaySection<DistanceType> find_best_proposals(
  const vector<HighwaySection<DistanceType> > &H,
  const vector<HighwaySection<DistanceType> > &P,
  const int &a, const int &b, const int &n) {
  // G stores the shortest path distance between all pairs
  vector<vector<DistanceType> >
    G(n, vector<DistanceType>(n, numeric_limits<DistanceType>::max()));

  // Build graph G based on existing highway sections H
  for (const HighwaySection<DistanceType> &h : H) {
    G[h.x][h.y] = G[h.y][h.x] = h.distance;
  }
  // Perform Floyd Warshall to build the shortest path between vertices
  Floyd_Warshall(G);

  // Examine each proposal for shorter distance between a and b
  DistanceType min_dis_a_b = G[a][b];
  HighwaySection<DistanceType> best_proposal;
  for (const HighwaySection<DistanceType> &p : P) {
    if (G[a][p.x] != numeric_limits<DistanceType>::max() &&
        G[p.y][b] != numeric_limits<DistanceType>::max()) {
      if (min_dis_a_b < G[a][p.x] + p.distance + G[p.y][b]) {
        min_dis_a_b = G[a][p.x] + p.distance + G[p.y][b];
        best_proposal = p;
      }
      if (min_dis_a_b < G[a][p.y] + p.distance + G[p.x][b]) {
        min_dis_a_b = G[a][p.y] + p.distance + G[p.x][b];
        best_proposal = p;
      }
    }
  }
  return best_proposal;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, m, k;
  if (argc == 2) {
    n = atoi(argv[1]);
    m = 1 + rand() % (n * (n - 1) / 2);
    k = 1 + rand() % (n * (n - 1) / 2 - m);
  } else if (argc == 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    k = 1 + rand() % (n * (n - 1) / 2 - m);
  } else {
    n = 1 + rand() % 100;
    m = 1 + rand() % (n * (n - 1) / 2);
    k = 1 + rand() % (n * (n - 1) / 2 - m);
  }
  vector<vector<bool> > have_edges(n, vector<bool>(n, false));
  vector<HighwaySection<double> > H;  // existing highway sections
  for (int i = 0; i < m; ++i) {
    int a, b;
    do {
      a = rand() % n, b = rand() % n;
    } while (a == b || have_edges[a][b] == true);
    have_edges[a][b] = have_edges[b][a] = true;
    H.emplace_back(HighwaySection<double>{a, b, static_cast<double>(rand())});
  }
  vector<HighwaySection<double> > P;  // proposals
  for (int i = 0; i < k; ++i) {
    int a, b;
    do {
      a = rand() % n, b = rand() % n;
    } while (a == b || have_edges[a][b] == true);
    have_edges[a][b] = have_edges[b][a] = true;
    P.emplace_back(HighwaySection<double>{a, b, static_cast<double>(rand())});
  }
  int a, b;
  do {
    a = rand() % n, b = rand() % n;
  } while (a == b);
  HighwaySection<double> t = find_best_proposals(H, P, a, b, n);
  cout << t.x << ' ' << t.y << ' ' << t.distance << endl;
  return 0;
}
