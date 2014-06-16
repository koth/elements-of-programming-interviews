// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::pair;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int check_ans(vector<int> A) {
  sort(A.begin(), A.end());
  int res = 1;
  int pre = A[0], len = 1;
  for (size_t i = 1; i < A.size(); ++i) {
    if (A[i] == pre + 1) {
      ++len;
    } else if (A[i] != pre) {
      res = max(res, len);
      len = 1;
    }
    pre = A[i];
  }
  res = max(res, len);
  cout << res << endl;
  return res;
}

int find_longest_contained_range(const vector<int>& A) {
  if (A.empty()) {
    return 0;
  }

  unordered_set<int> t;  // records the unique appearance.
  // L[i] stores the upper range for i.
  unordered_map<int, int> L;
  // U[i] stores the lower range for i.
  unordered_map<int, int> U;
  for (size_t i = 0; i < A.size(); ++i) {
    if (t.emplace(A[i]).second) {
      L[A[i]] = U[A[i]] = A[i];
      // Merges with the interval starting on A[i] + 1.
      if (L.find(A[i] + 1) != L.cend()) {
        L[U[A[i]]] = L[A[i] + 1];
        U[L[A[i] + 1]] = U[A[i]];
        L.erase(A[i] + 1);
        U.erase(A[i]);
      }
      // Merges with the interval ending on A[i] - 1.
      if (U.find(A[i] - 1) != U.cend()) {
        U[L[A[i]]] = U[A[i] - 1];
        L[U[A[i] - 1]] = L[A[i]];
        U.erase(A[i] - 1);
        L.erase(A[i]);
      }
    }
  }

  auto m =
      max_element(L.cbegin(),
                  L.cend(),
                  [](const pair<int, int>& a, const pair<int, int>& b)
                  { return a.second - a.first < b.second - b.first; });
  return m->second - m->first + 1;
}

/*
int longest_range_len(int a, const unordered_set<int>& S, unordered_map<int, int>* L);

pair<int, int> find_longest_contained_range(const vector<int>& A) {
  // S records the existence of each entry in A.
  unordered_set<int> S;
  for (int a : A) {
    S.emplace(a);
  }

  int max_len = 0;
  pair<int, int> max_range(0, -1);
  // L stores the longest length ending at each A[i].
  unordered_map<int, int> L;
  for (int a : A) {
    int len = longest_range_len(a, S, &L);
    if (len > max_len) {
      max_len = len, max_range = {a - len + 1, a};
    }
  }
  return max_range;
}
*/

int longest_range_len(int a, const unordered_set<int>& S,
                      unordered_map<int, int>* L) {
  // Base case. If a does not exist.
  if (S.find(a) == S.end()) {
    return 0;
  }

  if (L->find(a) == L->end()) {
    (*L)[a] = longest_range_len(a - 1, S, L) + 1;
  }
  return (*L)[a];
}

// @include
int longest_contained_range(const vector<int>& A) {
  // S records the existence of each entry in A.
  unordered_set<int> S;
  for (int a : A) {
    S.emplace(a);
  }

  int result = 0;
  for (int a : A) {
    if (S.find(a) != S.end()) {
      int count = 1;
      S.erase(a);

      // Find the lower bound of contained range of a.
      int val = a - 1;
      while (S.find(val) != S.end()) {
        ++count;
        S.erase(val);
        --val;
      }

      // Find the upper bound of contained range of a.
      val = a + 1;
      while (S.find(val) != S.end()) {
        ++count;
        S.erase(val);
        ++val;
      }

      result = max(result, count);
    }
  }
  return result;
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    size_t n;
    if (argc == 2) {
      n = stoul(argv[1]);
    } else {
      uniform_int_distribution<size_t> dis(0, 10000);
      n = dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> dis_n(0, static_cast<int>(n));
    for (size_t i = 0; i < n; ++i) {
      A.emplace_back(dis_n(gen));
    }
    /*
    for (size_t i = 0; i < n; ++i) {
      cout << A[i] << " ";
    }
    cout << endl;
    //*/
    assert(find_longest_contained_range(A) == check_ans(A));
    /*
    auto res = find_longest_contained_range(A);
    cout << "res = " << res.first << ", " << res.second << endl;
    assert(res.second - res.first + 1 == find_longest_contained_range(A));
    */
    assert(longest_contained_range(A) == check_ans(A));
  }
  return 0;
}
