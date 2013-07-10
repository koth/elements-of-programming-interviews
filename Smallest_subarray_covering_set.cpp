#include <iostream>
#include <list>
#include <cassert>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#ifdef __clang__
#include <unordered_map>
#include <unordered_set>
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#endif
#include <vector>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += rand() % 26 + 'a';
  }
  return ret;
}

pair<int, int> find_smallest_subarray_covering_subset(
  istringstream &sin, const vector<string> &Q) {
  list<int> loc;
  unordered_map<string, list<int>::iterator> dict;
  for (const string &s : Q) {
    dict.emplace(s, loc.end());
  }

  pair<int, int> res(-1, -1);
  int idx = 0;
  string s;
  while (sin >> s) {
    auto it = dict.find(s);
    if (it != dict.end()) {
      if (it->second != loc.end()) {
        loc.erase(it->second);
      }
      loc.emplace_back(idx);
      it->second = --loc.end();
    }

    if (loc.size() == Q.size() &&
      ((res.first == -1 && res.second == -1) ||
       res.second - res.first > idx - loc.front())) {
      res = {loc.front(), idx};
    }
    ++idx;
  }
  return res;
}

// @include
pair<int, int> find_smallest_subarray_covering_subset(
    const vector<string> &A, const vector<string> &Q) {
  unordered_set<string> dict(Q.cbegin(), Q.cend());
  unordered_map<string, int> count_Q;
  int l = 0, r = 0;
  pair<int, int> res(-1, -1);
  while (r < static_cast<int>(A.size())) {
    // Keep moving r until it reaches end or count_Q has |Q| items
    while (r < static_cast<int>(A.size()) && count_Q.size() < Q.size()) {
      if (dict.find(A[r]) != dict.end()) {
        ++count_Q[A[r]];
      }
      ++r;
    }

    if (count_Q.size() == Q.size() &&
        ((res.first == -1 && res.second == -1) ||
         r - 1 - l < res.second - res.first)) {
      res = {l, r - 1};
    }

    // Keep moving l until it reaches end or count_Q has less |Q| items
    while (l < r && count_Q.size() == Q.size()) {
      if (dict.find(A[l]) != dict.end()) {
        auto it = count_Q.find(A[l]);
        if (--(it->second) == 0) {
          count_Q.erase(it);
          if ((res.first == -1 && res.second == -1) ||
              r - 1 - l < res.second - res.first) {
            res = {l, r - 1};
          }
        }
      }
      ++l;
    }
  }
  return res;
}
// @exclude

// O(n^2) solution
int check_ans(const vector<string> &A, const vector<string> &Q) {
  unordered_set<string> dict;
  for (const string &s : Q) {
    dict.emplace(s);
  }

  pair<int, int> ans(0, A.size() - 1);
  for (int l = 0; l < A.size(); ++l) {
    unordered_map<string, int> count;
    for (int r = l; r < A.size() && r - l < ans.second - ans.first; ++r) {
      if (dict.find(A[r]) != dict.end()) {
        ++count[A[r]];
      }
      if (count.size() == Q.size()) {
        if (r - l < ans.second - ans.first) {
          ans = {l, r};
        }
        break;
      }
    }
    count.clear();
  }
  return ans.second - ans.first;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<string> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand_string(1 + rand() % 10));
    }
    /*
    for (int i = 0; i < A.size(); ++i) {
      cout << A[i] << ' ';
    }
    cout << endl;
    */
    unordered_set<string> dict;
    string s;
    for (int i = 0; i < A.size(); ++i) {
      dict.emplace(A[i]);
      s += A[i];
      s += ' ';
    }
    int m = 1 + rand() % dict.size();
    vector<string> Q;
    for (auto it = dict.cbegin(); it != dict.cend(); ++it) {
      Q.emplace_back(*it);
      if (--m == 0) {
        break;
      }
    }

    /*
    for (int i = 0; i < Q.size(); ++i) {
      cout << Q[i] << ' ';
    }
    cout << endl;
    */
    pair<int, int> res(find_smallest_subarray_covering_subset(A, Q));
    cout << res.first << ", " << res.second << endl;
    dict.clear();
    for (int i = 0; i < Q.size(); ++i) {
      dict.emplace(Q[i]);
    }
    for (int i = res.first; i <= res.second; ++i) {
      if (dict.find(A[i]) != dict.end()) {
        dict.erase(A[i]);
      }
    }
    assert(dict.empty() == true);
    istringstream sin(s);
    pair<int, int> res2(find_smallest_subarray_covering_subset(sin, Q));
    cout << res2.first << ", " << res2.second << endl;
    dict.clear();
    for (int i = 0; i < Q.size(); ++i) {
      dict.emplace(Q[i]);
    }
    for (int i = res.first; i <= res.second; ++i) {
      if (dict.find(A[i]) != dict.end()) {
        dict.erase(A[i]);
      }
    }
    assert(dict.empty() == true);
    assert(res.second - res.first == res2.second - res2.first);
    assert(res.second - res.first == check_ans(A, Q));
  }
  return 0;
}
