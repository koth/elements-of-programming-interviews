#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// @include
int backtrace(const vector<int> &F, int idx) {
  while (F[idx] != idx) {
    idx = F[idx];
  }
  return idx;
}

/*
 * A and B encode pairwise equivalences on a cardinality N set whose elements
 * are indexed by 0,1,2,...,N-1.
 *
 * For example A[i] = 6 and B[i] = 0 indicates that the 6 and 0 are to be
 * grouped into the same equivalence class.
 *
 * We return the weakest equivalence relation implied by A and B in an array
 * F of length N; F[i] holds the smallest index of all the elements that
 * i is equivalent to.
 */
vector<int> compute_equival_classes(const vector<int> &A,
                                    const vector<int> &B) {
  // Each element maps to itself
  vector<int> F(A.size());
  iota(F.begin(), F.end(), 0);

  for (int i = 0; i < A.size(); ++i) {
    int a = backtrace(F, A[i]), b = backtrace(F, B[i]);
    a < b ? F[b] = a : F[a] = b;
  }

  // Generate the weakest equivalence relation
  for (int &f : F) {
    while (f != F[f]) {
      f = F[f];
    }
  }
  return F;
}
// @exclude

int main(int argc, char *argv[]) {
  vector<int> A{1, 2, 2, 3, 5, 6};
  vector<int> B{2, 4, 1, 0, 2, 0};
  vector<int> res = compute_equival_classes(A, B);
  copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
  return 0;
}
