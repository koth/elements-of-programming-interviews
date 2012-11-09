#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <limits>

using namespace std;

// @include
template <typename T>
T distance(const vector<vector<T> > &arrs, const vector<T> &idx) {
  T dis = numeric_limits<T>::min();
  for (int i = 0; i < idx.size(); ++i) {
    for (int j = i + 1; j < idx.size(); ++j) {
      dis = max(dis, abs(arrs[i][idx[i]] - arrs[j][idx[j]]));
    }
  }
  return dis;
}

template <typename T>
class ArrData {
  public:
    int idx;
    T val;

    bool operator<(const ArrData &a) const {
      return val > a.val;
    }
};

template <typename T>
T find_min_distance_sorted_arrays(const vector<vector<T> > &arrs) {
  // Pointers for each of arrs
  vector<int> idx(arrs.size(), 0);
  T min_dis = numeric_limits<T>::max();
  priority_queue<ArrData<T>, vector<ArrData<T> > > min_heap;

  // Each of arrs puts its minimum element into min_heap
  for (int i = 0; i < arrs.size(); ++i) {
    if (idx[i] >= arrs[i].size()) {
      return min_dis;
    }
    min_heap.emplace(ArrData<T>{i, arrs[i][idx[i]]});
  }

  while (true) {
    min_dis = min(min_dis, distance(arrs, idx));
    ArrData<T> arr(min_heap.top());
    min_heap.pop();
    // Return if there is no remaining element in one array
    if (++idx[arr.idx] >= arrs[arr.idx].size()) {
      return min_dis;
    }
    min_heap.emplace(ArrData<T>{arr.idx, arrs[arr.idx][idx[arr.idx]]});
  }
}
// @exclude

template <typename T>
void rec_gen_answer(const vector<vector<T> > &arrs, vector<int> &idx, int level, T &ans) {
  if (level == arrs.size()) {
    ans = min(distance(arrs, idx), ans);
    return;
  }
  for (int i = 0; i < arrs[level].size(); ++i) {
    idx[level] = i;
    rec_gen_answer(arrs, idx, level + 1, ans);
  }
}

template <typename T>
T brute_force_gen_answer(const vector<vector<T> > &arrs) {
  T ans = numeric_limits<T>::max();
  vector<int> idx(arrs.size());
  rec_gen_answer(arrs, idx, 0, ans);
  cout << ans << endl;
  return ans;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<vector<int> > arrs;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 5;
    }
    arrs.resize(n);
    for (int i = 0; i < n; ++i) {
      int size = 1 + rand() % 100;
      for (int j = 0; j < size; ++j) {
        arrs[i].emplace_back(rand());
      }
      sort(arrs[i].begin(), arrs[i].end());
    }
    cout << find_min_distance_sorted_arrays<int>(arrs) << endl;
    assert(brute_force_gen_answer(arrs) == find_min_distance_sorted_arrays(arrs));
  }
  return 0;
}
