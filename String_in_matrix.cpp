#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>
#include <ctime>
#include <cstdlib>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

void rand_matrix(vector<vector<int> > &matrix) {
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      matrix[i][j] = rand() % matrix.size();
    }
  }
}

// @include
class HashTuple {
  public:
    size_t operator()(const tuple<int, int, int> &t) const {
      return hash<int>()(get<0>(t)) ^ hash<int>()(get<1>(t)) ^
             hash<int>()(get<2>(t));
    }
};

bool match_helper(const vector<vector<int> > &A, const vector<int> &S,
                  unordered_set<tuple<int, int, int>, HashTuple> cache,
                  int i, int j, int len) {
  if (S.size() == len) {
    return true;
  }

  if (i < 0 || i >= A.size() || j < 0 || j >= A[i].size() ||
      cache.find(make_tuple(i, j, len)) != cache.cend()) {
    return false;
  }

  if (A[i][j] == S[len] &&
      (match_helper(A, S, cache, i - 1, j, len + 1) ||
       match_helper(A, S, cache, i + 1, j, len + 1) ||
       match_helper(A, S, cache, i, j - 1, len + 1) ||
       match_helper(A, S, cache, i, j + 1, len + 1))) {
    return true;
  }
  cache.insert(make_tuple(i, j, len));
  return false;
}

bool match(const vector<vector<int> > &A, const vector<int> &S) {
  unordered_set<tuple<int, int, int>, HashTuple> cache;
  for (int i = 0; i < A.size(); ++i) { 
    for (int j = 0; j < A[i].size(); ++j) {
      if (match_helper(A, S, cache, i, j, 0)) {
        return true;
      }
    }
  }
  return false;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 10;
  }
  vector<vector<int> > A(n, vector<int>(n));
  rand_matrix(A);
  for (int i = 0; i < A.size(); ++i) { 
    for (int j = 0; j < A[i].size(); ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "S = ";
  vector<int> S(1 + rand() % (n * n >> 1));
  for (int i = 0; i < S.size(); ++i) {
    S[i] = rand() % n;
  }
  copy(S.begin(), S.end(), ostream_iterator<int>(cout, " "));
  cout << endl << boolalpha << match(A, S) << endl;
  return 0;
}
