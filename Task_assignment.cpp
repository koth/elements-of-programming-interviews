#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;

// @include
template <typename T>
vector<pair<T, T>> task_assignment(vector<T> A) {
  sort(A.begin(), A.end());
  vector<pair<T, T>> P;
  for (int i = 0, j = A.size() - 1; i < j; ++i, --j) {
    P.emplace_back(A[i], A[j]);
  }
  return P;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 10000;
  }
  vector<int> A;
  for (size_t i = 0; i < n; ++i) {
    A.emplace_back(rand() % 1000);
  }
  vector<pair<int, int>> P(task_assignment(A));
  int max = numeric_limits<int>::min();
  for (size_t i = 0; i < P.size(); ++i) {
    if (P[i].first + P[i].second > max) {
      max = P[i].first + P[i].second;
    }
  }
  cout << max << endl;
  return 0;
}
