// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::numeric_limits;
using std::random_device;
using std::set;
using std::uniform_int_distribution;
using std::vector;

template <typename T>
T distance(const vector<vector<T>>& arrs, const vector<int>& idx) {
  T max_T = numeric_limits<T>::min(), min_T = numeric_limits<T>::max();
  for (int i = 0; i < idx.size(); ++i) {
    max_T = max(max_T, arrs[i][idx[i]]);
    min_T = min(min_T, arrs[i][idx[i]]);
  }
  return max_T - min_T;
}

// @include
template <typename T>
struct ArrData {
  const bool operator<(const ArrData& a) const {
    if (val != a.val) {
      return val < a.val;
    } else {
      return idx < a.idx;
    }
  }

  int idx;
  T val;
};

template <typename T>
T find_min_distance_sorted_arrays(const vector<vector<T>>& arrs) {
  // Pointers for each of arrs
  vector<int> idx(arrs.size(), 0);
  T min_dis = numeric_limits<T>::max();
  set<ArrData<T>> current_heads;

  // Each of arrs puts its minimum element into current_heads
  for (int i = 0; i < arrs.size(); ++i) {
    if (idx[i] >= arrs[i].size()) {
      return min_dis;
    }
    current_heads.emplace(ArrData<T>{i, arrs[i][idx[i]]});
  }

  while (true) {
    min_dis = min(min_dis, current_heads.crbegin()->val -
                           current_heads.cbegin()->val);
    int tar = current_heads.cbegin()->idx;
    // Return if there is no remaining element in one array
    if (++idx[tar] >= arrs[tar].size()) {
      return min_dis;
    }
    current_heads.erase(current_heads.begin());
    current_heads.emplace(ArrData<T>{tar, arrs[tar][idx[tar]]});
  }
}
// @exclude

template <typename T>
void rec_gen_answer(const vector<vector<T>>& arrs, vector<int>& idx, int level,
                    T& ans) {
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
T brute_force_gen_answer(const vector<vector<T>>& arrs) {
  T ans = numeric_limits<T>::max();
  vector<int> idx(arrs.size());
  rec_gen_answer(arrs, idx, 0, ans);
  cout << ans << endl;
  return ans;
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<vector<int>> arrs;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 5);
      n = dis(gen);
    }
    arrs.resize(n);
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(1, 40);
      int size = dis(gen);
      for (int j = 0; j < size; ++j) {
        uniform_int_distribution<int> dis(0, 9999);
        arrs[i].emplace_back(dis(gen));
      }
      sort(arrs[i].begin(), arrs[i].end());
    }
    int ans = find_min_distance_sorted_arrays<int>(arrs);
    cout << ans << endl;
    assert(brute_force_gen_answer(arrs) == ans);
  }
  return 0;
}
