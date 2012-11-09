#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// @include
// Return pair<int, int>(duplicate, missing)
pair<int, int> find_duplicate_missing(const vector<int> &A) {
  int sum = 0, square_sum = 0;
  for (int i = 0; i < A.size(); ++i) {
    sum += i - A[i], square_sum += i * i - A[i] * A[i];
  }
  return {(square_sum / sum - sum) >> 1, (square_sum / sum + sum) >> 1};
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 2 + rand() % 10000;
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(i);
    }
    int missing_idx = rand() % n;
    int missing = A[missing_idx];
    int dup_idx = rand() % n;
    while (dup_idx == missing_idx) {
      dup_idx = rand() % n;
    }
    int dup = A[dup_idx];
    A[missing_idx] = dup;
    pair<int, int> ans = find_duplicate_missing(A);
    cout << "times = " << times << endl;
    cout << dup << ' ' << missing << endl;
    cout << ans.first << ' ' << ans.second << endl;
    assert(ans.first == dup && ans.second == missing);
  }
  return 0;
}
