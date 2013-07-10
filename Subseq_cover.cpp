#include <iostream>
#include <cassert>
#include <unordered_set>
#include <iterator>
#include <vector>
#include <string>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

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

// @include
pair<int, int> find_smallest_sequentially_covering_subset(
  const vector<string> &A, const vector<string> &Q) {
  unordered_map<string, int> K;  // stores the order of each Q[i]
  vector<int> L(Q.size(), -1), D(Q.size(), numeric_limits<int>::max());

  // Initialize K
  for (int i = 0; i < Q.size(); ++i) {
    K.emplace(Q[i], i);
  }

  pair<int, int> res(-1, A.size());  // default value
  for (int i = 0; i < A.size(); ++i) {
    auto it = K.find(A[i]);
    if (it != K.cend()) {
      if (it->second == 0) {  // first one, no predecessor
        D[0] = 1;  // base condition
      } else if (D[it->second - 1] != numeric_limits<int>::max()) {
        D[it->second] = i - L[it->second - 1] + D[it->second - 1];
      }
      L[it->second] = i;

      if (it->second == Q.size() - 1 &&
          D.back() < res.second - res.first + 1) {
        res = {i - D.back() + 1, i};
      }
    }
  }
  return res;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  //srand(1);
  vector<string> A3 = {"0","1","2","3","4","5","6","7","8","9","2","4","6","10","10","10","3","2","1","0"};
  vector<string> subseq4 = {"0","2","9","4","6"};
  pair<int, int> rr = find_smallest_sequentially_covering_subset(A3, subseq4);
  assert(rr.first == 0 && rr.second == 12);
  for (int times = 0; times < 1000; ++times) {
    int n;
    vector<string> A;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand()% 10000;
    }
    generate_n(back_inserter(A), n, [&]{ return rand_string(1 + rand() % 5); });
    unordered_set<string> dict;
    copy(A.begin(), A.end(), inserter(dict, dict.end()));
    //*
    cout << "A = ";
    copy(A.begin(), A.end(), ostream_iterator<string>(cout, ","));
    cout << endl;
    //*/
    int m = 1 + rand() % min(static_cast<int>(dict.size()), 10);
    vector<string> Q;
    auto it = dict.begin();
    generate_n(back_inserter(Q), m, [&]{ return *it++; });
    //*
    cout << "Q = ";
    copy(Q.begin(), Q.end(), ostream_iterator<string>(cout, ","));
    cout << endl;
    //*/

    pair<int, int> res(find_smallest_sequentially_covering_subset(A, Q));
    cout << res.first << ", " << res.second << endl;
    if (res.first != -1 && res.second != Q.size()) {
      if (res.first != res.second)
        cout << res.first << ", " << res.second << endl;
      dict.clear();
      copy(Q.begin(), Q.end(), inserter(dict, dict.end()));
      for (int i = res.first; i <= res.second; ++i) {
        if (dict.find(A[i]) != dict.end()) {
          dict.erase(A[i]);
        }
      }
      assert(dict.empty());
    }
  }
  return 0;
}
