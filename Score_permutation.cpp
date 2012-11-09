#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
int count_permutations(const int &k, const vector<int> &score_ways) {
  vector<int> permutations(k + 1, 0);
  permutations[0] = 1;  // 1 way to reach 0
  for (int i = 0; i <= k; ++i) {
    for (const int &score : score_ways) {
      if (i >= score) {
        permutations[i] += permutations[i - score];
      }
    }
  }
  return permutations[k];
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
  cout << count_permutations(k, score_ways) << endl;
  return 0;
}
