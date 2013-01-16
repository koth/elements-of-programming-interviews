#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
int celebrity_finding(const vector<vector<bool> > &F) {
  // Start checking the relation from F[0][1]
  int i = 0, j = 1;
  while (j < F.size()) {
    if (F[i][j] == true) {
      i = j++;  // all candidates j' < j are not celebrity candidates
    } else {  // F[i][j] == false
      ++j;  // i is still a celebrity candidate but j is not
    }
  }
  return i;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc > 1) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    vector<vector<bool> > graph(n, vector<bool>(n));
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        graph[i][j] = ((rand() & 1) ? true : false);
      }
      graph[i][i] = false;
    }
    int celebrity = rand() % n;
    for (size_t i = 0; i < n; ++i) {
      graph[i][celebrity] = true;
    }
    for (size_t j = 0; j < n; ++j) {
      graph[celebrity][j] = false;
    }
    cout << celebrity_finding(graph) << endl;
    assert(celebrity == celebrity_finding(graph));
  }
  return 0;
}
