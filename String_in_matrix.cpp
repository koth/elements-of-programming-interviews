// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::get;
using std::hash;
using std::ostream_iterator;
using std::random_device;
using std::tuple;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

void rand_matrix(vector<vector<int>>* matrix) {
  default_random_engine gen((random_device())());
  for (int i = 0; i < matrix->size(); ++i) {
    for (int j = 0; j < (*matrix)[i].size(); ++j) {
      uniform_int_distribution<int> dis(0, matrix->size() - 1);
      (*matrix)[i][j] = dis(gen);
    }
  }
}

struct HashTuple;

bool match_helper(const vector<vector<int>>& A, const vector<int>& S,
                  unordered_set<tuple<int, int, int>, HashTuple>* cache,
                  int i, int j, int len);

// @include
struct HashTuple {
  size_t operator()(const tuple<int, int, int>& t) {
    return hash<int>()(get<0>(t)) ^ hash<int>()(get<1>(t)) ^
           hash<int>()(get<2>(t));
  }
};

bool match(const vector<vector<int>>& A, const vector<int>& S) {
  unordered_set<tuple<int, int, int>, HashTuple> cache;
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      if (match_helper(A, S, &cache, i, j, 0)) {
        return true;
      }
    }
  }
  return false;
}

bool match_helper(const vector<vector<int>>& A, const vector<int>& S,
                  unordered_set<tuple<int, int, int>, HashTuple>* cache,
                  int i, int j, int len) {
  if (S.size() == len) {
    return true;
  }

  if (i < 0 || i >= A.size() || j < 0 || j >= A[i].size() ||
      cache->find({i, j, len}) != cache->cend()) {
    return false;
  }

  if (A[i][j] == S[len] && (match_helper(A, S, cache, i - 1, j, len + 1) ||
                            match_helper(A, S, cache, i + 1, j, len + 1) ||
                            match_helper(A, S, cache, i, j - 1, len + 1) ||
                            match_helper(A, S, cache, i, j + 1, len + 1))) {
    return true;
  }
  cache->emplace(i, j, len);
  return false;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(2, 10);
    n = dis(gen);
  }
  vector<vector<int>> A(n, vector<int>(n));
  rand_matrix(&A);
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "S = ";
  uniform_int_distribution<int> dis(1, n * n >> 1);
  vector<int> S(1 + dis(gen));
  for (size_t i = 0; i < S.size(); ++i) {
    uniform_int_distribution<int> dis(0, n - 1);
    S[i] = dis(gen);
  }
  copy(S.begin(), S.end(), ostream_iterator<int>(cout, " "));
  cout << endl << boolalpha << match(A, S) << endl;
  return 0;
}
