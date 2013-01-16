#include <iostream>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

// @include
vector<int> next_permutation(vector<int> p) {
  int k = p.size() - 2;
  while (k >= 0 && p[k] >= p[k + 1]) {
    --k;
  }
  if (k == -1) {
    return {};  // p is the last permutation
  }

  int l;
  for (int i = k + 1; i < p.size(); ++i) {
    if (p[i] > p[k]) {
      l = i;
    } else {
      break;
    }
  }
  swap(p[k], p[l]);

  // Produce the lexicographically minimal permutation
  reverse(p.begin() + k + 1, p.end());
  return p;
}
// @exclude

int main(int argc, char *argv[]){
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    vector<int> p;
    if (argc > 2) {
      for (size_t i = 1; i < argc; ++i) {
        p.emplace_back(atoi(argv[i]));
      }
    } else {
      int n = (argc == 2 ? atoi(argv[1]) : 1 + rand() % 100);
      for (size_t i = 0; i < n; ++i) {
        p.emplace_back(rand() % n);
      }
    }
    /*
    for (size_t i = 0; i < p.size(); ++i) {
      cout << p[i] << ' ';
    }
    cout << endl;
    //*/
    vector<int> ans(next_permutation(p));
    next_permutation(p.begin(), p.end());
    /*
    for (const int &a : ans) {
      cout << a << ' ';
    }
    cout << endl;
    for (const int &a : p) {
      cout << a << ' ';
    }
    cout << endl;
    //*/
    assert(equal(ans.cbegin(), ans.cend(), p.cbegin()));
  }
  return 0;
}
