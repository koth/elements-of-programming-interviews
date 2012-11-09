#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
void apply_permutation1(vector<int> &perm, vector<T> &A) {
  for (int i = 0; i < A.size(); ++i) {
    if (perm[i] >= 0) {
      int a = i;
      T temp = A[i];
      do {
        int next_a = perm[a];
        T next_temp = A[next_a];
        A[next_a] = temp;
        // Mark a as visited by using the sign bit
        perm[a] -= perm.size();
        a = next_a, temp = next_temp;
      } while (a != i);
    }
  }

  // Restore perm back
  size_t size = perm.size();
  for_each(perm.begin(), perm.end(), [size](T &x) { x += size; });
}

// @include
template <typename T>
void apply_permutation2(vector<int> &perm, vector<T> &A) {
  for (int i = 0; i < A.size(); ++i) {
    // Traverse the cycle to see if i is the min element
    bool is_min = true;
    int j = perm[i];
    while (j != i) {
      if (j < i) {
        is_min = false;
        break;
      }
      j = perm[j];
    }

    if (is_min) {
      int a = i;
      T temp = A[i];
      do {
        int next_a = perm[a];
        T next_temp = A[next_a];
        A[next_a] = temp;
        a = next_a, temp = next_temp;
      } while (a != i);
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  for (int times = 0; times < 1000; ++times) {
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 100;
    }
    vector<int> A, perm;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(i);
      perm.emplace_back(i);
    }

    random_shuffle(perm.begin(), perm.end());
    copy(perm.begin(), perm.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    vector<int> B(A);
    apply_permutation1(perm, B);
    copy(B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    vector<int> C(A);
    apply_permutation2(perm, C);
    copy(C.begin(), C.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // check answer by comparing the two permutations
    for (int i = 0; i < B.size(); ++i) {
      assert(B[i] == C[i]);
    }
  }
  return 0;
}
