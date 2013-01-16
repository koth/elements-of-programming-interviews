#include <iostream>
#include <array>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
class Coordinate {
  public:
    int i, j;

    const bool operator==(const Coordinate& that) const {
      return (i == that.i && j == that.j);
    }
};

// Check cur is within maze and is a white pixel
bool is_feasible(const Coordinate &cur, const vector<vector<int> > &maze) {
  return (cur.i >= 0 && cur.i < maze.size() &&
          cur.j >= 0 && cur.j < maze[cur.i].size() &&
          maze[cur.i][cur.j] == 0);
}

// Perform DFS to find a feasible path
bool search_maze_helper(vector<vector<int> > &maze, const Coordinate &cur,
                        const Coordinate &e, vector<Coordinate> &path) {
  if (cur == e) {
    return true;
  }

  const array<array<int, 2>, 4> shift = {0, 1, 0, -1, 1, 0, -1, 0};
  for (const array<int, 2> &s : shift) {
    Coordinate next{cur.i + s[0], cur.j + s[1]};
    if (is_feasible(next, maze)) {
      maze[next.i][next.j] = 1;
      path.emplace_back(next);
      if (search_maze_helper(maze, next, e, path)) {
        return true;
      }
      path.pop_back();
    }
  }
  return false;
}

vector<Coordinate> search_maze(vector<vector<int> > maze, const Coordinate &s,
                               const Coordinate &e) {
  vector<Coordinate> path;
  maze[s.i][s.j] = 1;
  path.emplace_back(s);
  if (search_maze_helper(maze, s, e, path) == false) {
    path.pop_back();
  }
  return path;  // empty path means no path between s and e
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]);
      m = atoi(argv[2]);
    } else {
      n = 1 + rand() % 30;
      m = 1 + rand() % 30;
    }
    vector<vector<int> > maze(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        maze[i][j] = rand() & 1;
      }
    }
    vector<Coordinate> white;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (maze[i][j] == 0) {
          white.emplace_back(Coordinate{i, j});
        }
        cout << maze[i][j] << ' ';
      }
      cout << endl;
    }
    cout << endl;
    if (white.size()) {
      int start = rand() % white.size();
      int end = rand() % white.size();
      cout << white[start].i << ' ' << white[start].j << endl;
      cout << white[end].i << ' ' << white[end].j << endl;
      vector<Coordinate> path = search_maze(maze, white[start], white[end]);
      if (!path.empty()) {
        assert(white[start] == path.front() && white[end] == path.back());
      }
      for (int i = 0; i < path.size(); ++i) {
        if (i > 0) {
          assert(abs(path[i - 1].i - path[i].i) + abs(path[i - 1].j - path[i].j) == 1);
        }
        cout << '(' << path[i].i << ',' << path[i].j << ')' << endl;
      }
    }
  }
  return 0;
}
