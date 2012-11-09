#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>

using namespace std;

// @include
template <typename T>
void rearrange(vector<T> &A) {
  for (int i = 0; i < A.size() - 1; ++i) {
    if ((i & 1 && A[i] < A[i + 1]) || ((i & 1) == 0 && A[i] > A[i + 1])) {
      swap(A[i], A[i + 1]);
    }
  }
}
// @exclude

template <typename T>
void check_answer(const vector<T> &A) {
  for (int i = 0; i < A.size(); ++i) {
    if (i & 1) {
      assert(A[i] >= A[i - 1]);
      if (i < A.size() - 1) {
        assert(A[i] >= A[i + 1]);
      }
    } else {
      if (i > 0) {
        assert(A[i - 1] >= A[i]);
      }
      if (i < A.size() - 1) {
        assert(A[i + 1] >= A[i]);
      }
    }
  }
}

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
    for (int i = 0; i < n; ++i) {
      A.emplace_back(rand());
    }
    rearrange(A);
    /*
    for (const int &a : A) {
      cout << a << ' ';
    }
    cout << endl;
    */
    check_answer(A);
  }
  return 0;
}
