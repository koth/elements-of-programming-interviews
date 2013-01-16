#include <iostream>
#include <stack>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

template <typename HeightType>
class Player {
  public:
    HeightType height;

    const bool operator<(const Player &that) const {
      return height < that.height;
    }
};

template <typename HeightType>
class Team {
  private:
    vector<Player<HeightType> > members;

    vector<Player<HeightType> > sortHeightMembers(void) const {
      vector<Player<HeightType> > sorted_members(members);
      sort(sorted_members.begin(), sorted_members.end());
      return sorted_members;
    }

  public:
    const bool operator<(const Team &that) const {
      vector<Player<HeightType> > this_sorted(sortHeightMembers());
      vector<Player<HeightType> > that_sorted(that.sortHeightMembers());
      for (int i = 0; i < this_sorted.size() && i < that_sorted.size(); ++i) {
        if (this_sorted[i] < that_sorted[i] == false) {
          return false;
        }
      }
      return true;
    }

    Team(const vector<HeightType> &height) {
      for (const HeightType &h : height) {
        members.emplace_back(Player<HeightType>{h});
      }
    }
};

// @include
class GraphVertex {
  public:
    vector<GraphVertex*> edges;
    int maxDistance;
    bool visited;

    GraphVertex(void) : maxDistance(1), visited(false) {};
};

void DFS(GraphVertex* cur, stack<GraphVertex*> &vertex_order) {
  cur->visited = true;
  for (GraphVertex* &next : cur->edges) {
    if (next->visited == false) {
      DFS(next, vertex_order);
    }
  }
  vertex_order.emplace(cur);
}

stack<GraphVertex*> build_topological_ordering(vector<GraphVertex> &G) {
  stack<GraphVertex*> vertex_order;
  for (GraphVertex &g: G) {
    if (g.visited == false) {
      DFS(&g, vertex_order);
    }
  }
  return vertex_order;
}

int find_longest_path(stack<GraphVertex*> &vertex_order) {
  int max_distance = 0;
  while (vertex_order.empty() == false) {
    GraphVertex* u = vertex_order.top();
    max_distance = max(max_distance, u->maxDistance);
    for (GraphVertex* &v : u->edges) {
      v->maxDistance = max(v->maxDistance, u->maxDistance + 1);
    }
    vertex_order.pop();
  }
  return max_distance;
}

int find_largest_number_teams(vector<GraphVertex> &G) {
  stack<GraphVertex*> vertex_order(build_topological_ordering(G));
  return find_longest_path(vertex_order);
}
// @exclude

int main(int argc, char *argv[]) {
  vector<int> height(3);
  height[0] = 1, height[1] = 5, height[2] = 4;
  Team<int> t1(height);
  height[0] = 2, height[2] = 3, height[3] = 4;
  Team<int> t2(height);
  height[0] = 0, height[1] = 3, height[2] = 2;
  Team<int> t3(height);
  vector<GraphVertex> G(3);
  G[0].edges.emplace_back(&G[2]);
  G[1].edges.emplace_back(&G[2]);
  assert(2 == find_largest_number_teams(G));
  return 0;
}
