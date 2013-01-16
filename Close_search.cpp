#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

// @include
int close_search(const vector<int> &A, const int &k) {
  int idx = 0;
  while (idx < A.size() && A[idx] != k) {
    idx += abs(A[idx] - k);
  }
  return idx < A.size() ? idx : -1;  // -1 means no result
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<int> A;
    A.emplace_back(rand() % 10);
    for (size_t i = 1; i < n; ++i) {
      int shift = (rand() % 3) - 1;
      A.emplace_back(A[i - 1] + shift);
    }
    int k = rand() % 100;
    int ans = close_search(A, k);
    cout << ans << endl;
    if (ans != -1) {
      assert(A[ans] == k);
    } else {
      bool found = false;
      for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] == k) {
          found = true;
          break;
        }
      }
      assert(found == false);
    }
  }
  return 0;
}
