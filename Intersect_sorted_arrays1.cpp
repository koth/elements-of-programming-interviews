#include <iostream>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
template <typename T>
vector<T> intersect_arrs1(const vector<T> &A, const vector<T> &B) {
  vector<T> intersect;
  for (int i = 0; i < A.size(); ++i) {
    if (i == 0 || A[i] != A[i - 1]) {
      for (int j = 0; j < B.size(); ++j) {
        if (A[i] == B[j]) {
          intersect.emplace_back(A[i]);
          break;
        }
      }
    }
  }
  return intersect;
}
// @exclude

template <typename T>
vector<T> intersect_arrs2(const vector<T> &A, const vector<T> &B) {
  vector<T> intersect;
  for (int i = 0; i < A.size(); ++i) {
    if ((i == 0 || A[i] != A[i - 1]) && binary_search(B.begin(), B.end(), A[i])) {
      intersect.emplace_back(A[i]);
    }
  }
  return intersect;
}

template <typename T>
vector<T> intersect_arrs3(const vector<T> &A, const vector<T> &B) {
  vector<T> intersect;
  int i = 0, j = 0;
  while (i < A.size() && j < B.size()) {
    if (A[i] == B[j] && (i == 0 || A[i] != A[i - 1])) {
      intersect.emplace_back(A[i]);
      ++i, ++j;
    } else if (A[i] < B[j]) {
      ++i;
    } else {  // A[i] > B[j]
      ++j;
    }
  }
  return intersect;
}

template <typename T>
void check_ans(const vector<T> &a, const vector<T> &b, const vector<T> &c) {
  cout << a.size() << ' ' << b.size() << ' ' << c.size() << endl;
  assert(a.size() == b.size());
  assert(b.size() == c.size());
  for (int i = 0; i < a.size(); ++i) {
    // cout << a[i] << ' ';
    assert(a[i] == b[i]);
    assert(b[i] == c[i]);
  }
  //cout << endl;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    vector<int> A, B;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      n = 1 + rand() % 10000, m = 1 + rand() % 10000;
    }
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand() % n);
    }
    for (int j = 0; j < m; ++j) {
      B.emplace_back(rand() % m);
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<int> res1 = intersect_arrs1(A, B);
    vector<int> res2 = intersect_arrs2(A, B);
    vector<int> res3 = intersect_arrs3(A, B);
    check_ans(res1, res2, res3);
  }
  return 0;
}
