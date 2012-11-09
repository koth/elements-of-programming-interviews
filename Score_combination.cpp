#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
int count_combinations(const int &k, const vector<int> &score_ways) {
  vector<int> combinations(k + 1, 0);
  combinations[0] = 1;  // 1 way to reach 0
  for (const int &score : score_ways) {
    for (int j = score; j <= k; ++j) {
      combinations[j] += combinations[j - score];
    }
  }
  return combinations[k];
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int k;
  vector<int> score_ways;
  if (argc == 1) {
    k = rand() % 1000;
    score_ways.resize(1 + rand() % 50);
    for (int i = 0; i < score_ways.size(); ++i) {
      score_ways[i] = 1 + rand() % 1000;
    }
  } else if (argc == 2) {
    k = atoi(argv[1]);
    score_ways.resize(1 + rand() % 50);
    for (int i = 0; i < score_ways.size(); ++i) {
      score_ways[i] = 1 + rand() % 1000;
    }
  } else {
    k = atoi(argv[1]);
    for (int i = 2; i < argc; ++i) {
      score_ways.emplace_back(atoi(argv[i]));
    }
  }
  cout << count_combinations(k, score_ways) << endl;
  return 0;
}
