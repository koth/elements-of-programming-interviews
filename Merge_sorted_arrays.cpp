#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
class Compare {
  public:
    bool operator()(const pair<T, int> &lhs, const pair<T, int> &rhs) const {
      return lhs.first > rhs.first;
    }
};

template <typename T>
vector<T> merge_arrays(const vector<vector<T> > &S) {
  priority_queue<pair<T, int>, vector<pair<T, int> >, Compare<T> > min_heap;
  vector<int> S_idx(S.size(), 0);

  // Every array in S puts its smallest element in heap
  for (int i = 0; i < S.size(); ++i) {
    if (S[i].size() > 0) {
      min_heap.emplace(S[i][0], i);
      S_idx[i] = 1;
    }
  }

  vector<T> ret;
  while (!min_heap.empty()) {
    pair<T, int> p = min_heap.top();
    ret.emplace_back(p.first);
    // Add the smallest element into heap if possible
    if (S_idx[p.second] < S[p.second].size()) {
      min_heap.emplace(S[p.second][S_idx[p.second]++], p.second);
    }
    min_heap.pop();
  }
  return ret;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<vector<int> > S(n, vector<int>());
    cout << "n = " << n << endl;
    for (size_t i = 0; i < n; ++i) {
      S[i].resize(1 + rand() % 500);
      for (size_t j = 0; j < S[i].size(); ++j) {
        S[i][j] = ((rand() & 1) ? -1 : 1) * rand() % 10000;
      }
      sort(S[i].begin(), S[i].end());
    }
    /*
       for (size_t i = 0; i < n; ++i) {
       for (size_t j = 0; j < S[i].size(); ++j) {
       cout << S[i][j] << ' ';
       }
       cout << endl;
       }
     */
    vector<int> ans = merge_arrays(S);
    for (size_t i = 1; i < ans.size(); ++i) {
      assert(ans[i - 1] <= ans[i]);
    }
  }
  return 0;
}
